// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/EOSGameInstance.h"

#include "Interfaces/OnlineFriendsInterface.h"
#include "Interfaces/OnlineIdentityInterface.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Interfaces/OnlineUserInterface.h" 
#include "Kismet/GameplayStatics.h" 
#include "Menu/FriendInfo.h"
#include "Menu/InviteInfo.h"
#include "Menu/LoadingController.h"
#include "Menu/MenuController.h"
#include "Notification/InviteNotification.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

const FName TestSessionName = FName("Test Session");

UEOSGameInstance::UEOSGameInstance()
{
	bIsLoggedIn = false;
	bFriendsListInitiallyRead = false;
	NameSet = false;
	GameType = EGameType::Player;
}

void UEOSGameInstance::Init()
{
	Super::Init();

	OnlineSubsystem = IOnlineSubsystem::Get();
}

void UEOSGameInstance::Login()
{
	LoadingController = Cast<ALoadingController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (OnlineSubsystem)
	{
		if (IOnlineIdentityPtr Identity = OnlineSubsystem->GetIdentityInterface())
		{
			FOnlineAccountCredentials Credentials;
			if (GameType == EGameType::Player)
			{
				Credentials.Id = FString();
				Credentials.Token = FString();
				Credentials.Type = FString("accountportal");
			}
			else if (GameType == EGameType::Developer)
			{
				Credentials.Id = FString("127.0.0.1:9010");
				Credentials.Token = FString("TestClient1");
				Credentials.Type = FString("developer");
			}
			Identity->OnLoginCompleteDelegates->AddUObject(this, &UEOSGameInstance::OnLoginComplete);
			Identity->Login(0, Credentials);
		}
	}
}

void UEOSGameInstance::OnLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error)
{
	UE_LOG(LogTemp, Warning, TEXT("Log in success: %d"), bWasSuccessful);

	if (LoadingController)
	{
		LoadingController->SetLoggedIn();
	}

	bIsLoggedIn = bWasSuccessful;
	CreateSession();
	if (OnlineSubsystem)
	{
		if (IOnlineIdentityPtr Identity = OnlineSubsystem->GetIdentityInterface())
		{
			Identity->ClearOnLoginCompleteDelegates(0, this);
		}
	}
}

void UEOSGameInstance::CreateSession()
{
	if (bIsLoggedIn)
	{
		if (OnlineSubsystem)
		{
			if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
			{
				FOnlineSessionSettings SessionSettings;
				SessionSettings.bIsDedicated = false;
				SessionSettings.bShouldAdvertise = true;
				SessionSettings.bIsLANMatch = false;
				SessionSettings.NumPublicConnections = 5;
				SessionSettings.bAllowJoinInProgress = true;
				SessionSettings.bAllowJoinViaPresence = true;
				SessionSettings.bUsesPresence = true;
				SessionSettings.bUseLobbiesIfAvailable = false;

				SessionSettings.Set(SEARCH_KEYWORDS, FString("FreddyTestLobby"), EOnlineDataAdvertisementType::ViaOnlineService);

				SessionPtr->OnCreateSessionCompleteDelegates.AddUObject(this, &UEOSGameInstance::OnCreateSessionComplete);
				SessionPtr->CreateSession(0, TestSessionName, SessionSettings);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot Create Session: Not Logged In"));
	}
}

void UEOSGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("Session creation success: %d"), bWasSuccessful);

	if (LoadingController)
	{
		LoadingController->SetSessionCreated();
		LoadingController->OpenMainMenu();
	}

	if (OnlineSubsystem)
	{
		if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
		{
			//SessionPtr->OnSessionInviteReceivedDelegates.AddUObject(this, &UEOSGameInstance::OnSessionInviteReceived);
			FOnSessionInviteReceivedDelegate InviteReceivedDelegate = FOnSessionInviteReceivedDelegate::CreateUObject(this, &UEOSGameInstance::OnSessionInviteReceived);
			SessionPtr->AddOnSessionInviteReceivedDelegate_Handle(InviteReceivedDelegate);
			FOnSessionUserInviteAcceptedDelegate InviteAcceptedDelegate = FOnSessionUserInviteAcceptedDelegate::CreateUObject(this, &UEOSGameInstance::OnSessionUserInviteAccepted);
			SessionPtr->AddOnSessionUserInviteAcceptedDelegate_Handle(InviteAcceptedDelegate);

			GetAllFriends();

			SessionPtr->ClearOnCreateSessionCompleteDelegates(this);
		}
	}
}

void UEOSGameInstance::DestroySession()
{
	if (bIsLoggedIn)
	{
		if (OnlineSubsystem)
		{
			if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
			{
				SessionPtr->OnDestroySessionCompleteDelegates.AddUObject(this, &UEOSGameInstance::OnDestroySessionComplete);
				SessionPtr->DestroySession(TestSessionName);
			}
		}
	}
}

void UEOSGameInstance::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	UE_LOG(LogTemp, Warning, TEXT("Session destroy success: %d"), bWasSuccessful);

	if (OnlineSubsystem)
	{
		if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
		{
			SessionPtr->OnJoinSessionCompleteDelegates.AddUObject(this, &UEOSGameInstance::OnJoinSessionComplete);
			if (SessionToJoin)
			{
				if (SessionPtr->JoinSession(0, TestSessionName, *SessionToJoin))
				{
					UE_LOG(LogTemp, Warning, TEXT("Joined session %s"), *SessionName.ToString());
				}
			}
			SessionPtr->ClearOnDestroySessionCompleteDelegates(this);
		}
	}
}

void UEOSGameInstance::GetAllFriends()
{
	if (bIsLoggedIn)
	{
		if (OnlineSubsystem)
		{
			if (IOnlineFriendsPtr FriendsPtr = OnlineSubsystem->GetFriendsInterface())
			{
				FriendsPtr->ReadFriendsList(0, FString(""), FOnReadFriendsListComplete::CreateUObject(this, &UEOSGameInstance::OnGetAllFriendsComplete));
			}
		}
	}
}

void UEOSGameInstance::OnGetAllFriendsComplete(int32 LocalUserNum, bool bWasSuccessful, const FString& ListName, const FString& ErrorStr)
{
	UE_LOG(LogTemp, Warning, TEXT("Get friends success: %d"), bWasSuccessful);
	if (bWasSuccessful)
	{
		bFriendsListInitiallyRead = true;
		if (OnlineSubsystem)
		{
			if (IOnlineFriendsPtr FriendsPtr = OnlineSubsystem->GetFriendsInterface())
			{
				TArray<TSharedRef<FOnlineFriend>> FriendsList;
				if (FriendsPtr->GetFriendsList(0, ListName, FriendsList))
				{
					Friends.Empty();
					int CurrentIndex = 0;
					for (TSharedRef<FOnlineFriend> Friend : FriendsList)
					{
						FString FriendName = Friend.Get().GetDisplayName();
						UFriendInfo* NewFriend = NewObject<UFriendInfo>(this);
						NewFriend->Index = CurrentIndex;
						NewFriend->UniqueId = Friend.Get().GetUserId();
						NewFriend->UniqueIdStrChopped = GetChoppedNetId(Friend.Get().GetUserId()->ToString());
						NewFriend->DisplayName = FriendName;
						for (auto Invite : Invites)
						{
							if (Invite->FromIdStrChopped == NewFriend->UniqueIdStrChopped)
							{
								NewFriend->PendingInvite = true;
							}
						}
						Friends.Emplace(NewFriend);
						CurrentIndex += 1;
					}
					if (MenuController)
					{
						MenuController->UpdateFriends();
					}
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("Failed get friends list"));
				}
			}
		}
	}
}

void UEOSGameInstance::InviteFriendToSession(int FriendIndex)
{
	if (bIsLoggedIn)
	{
		if (OnlineSubsystem)
		{
			if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
			{
				if (SessionPtr->SendSessionInviteToFriend(0, TestSessionName, *((Friends[FriendIndex])->UniqueId.Pin()).Get()))
				{
					UE_LOG(LogTemp, Warning, TEXT("Successfully invited friend %d"), FriendIndex);
				}
			}
		}
	}
}

void UEOSGameInstance::AcceptFriendInvite(int FriendIndex)
{
	for (auto Invite : Invites)
	{
		if (Invite->FromIdStrChopped == Friends[FriendIndex]->UniqueIdStrChopped)
		{
			StartJoinSession(Invite->InviteResult);
		}
	}
}

void UEOSGameInstance::OnSessionInviteReceived(const FUniqueNetId& UserId, const FUniqueNetId& FromId, const FString& AppId, const FOnlineSessionSearchResult& InviteResult)
{
	if (bIsLoggedIn)
	{
		if (OnlineSubsystem)
		{
			if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
			{
				if (IOnlineIdentityPtr IdentityPtr = OnlineSubsystem->GetIdentityInterface())
				{
					FString FriendName = "someone outside your friends list.";
					if (bFriendsListInitiallyRead)
					{
						for (auto Friend : Friends)
						{
							if (FromId == *Friend->UniqueId.Pin().Get())
							{
								FriendName = Friend->DisplayName;
								Friend->PendingInvite = true;
							}
						}
					}

					UInviteInfo* NewInvite = NewObject<UInviteInfo>(this);
					NewInvite->Index = Invites.Num();
					NewInvite->FromId = &FromId;
					NewInvite->InviteResult = &InviteResult;
					NewInvite->FromIdStrChopped = GetChoppedNetId(FromId.ToString());

					Invites.Emplace(NewInvite);

					UInviteNotification* NewNotification = NewObject<UInviteNotification>(this);
					NewNotification->InviterName = FriendName;
					NewNotification->FromIdStr = FromId.ToString();
					AddNewNotification(NewNotification);
				}
			}
		}
	}
}

void UEOSGameInstance::OnSessionUserInviteAccepted(const bool bWasSuccess, const int32 ControllerId, TSharedPtr<const FUniqueNetId> UserId, const FOnlineSessionSearchResult& InviteResult)
{
	StartJoinSession(&InviteResult);
}

void UEOSGameInstance::RespondToInvite(FString FromIdStr, EInviteResponse InviteResponse)
{
	switch (InviteResponse)
	{
		case EInviteResponse::Accept:
		{
			for (auto Invite : Invites)
			{
				if (Invite->FromId->ToString() == FromIdStr)
				{
					StartJoinSession(Invite->InviteResult);
				}
			}
			break;
		}
		case EInviteResponse::Invite:
		{
			break;
		}
		case EInviteResponse::Ignore:
		{
			break;
		}
	}
}

void UEOSGameInstance::StartJoinSession(const FOnlineSessionSearchResult* InviteResult)
{
	if (bIsLoggedIn)
	{
		if (OnlineSubsystem)
		{
			if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
			{
				SessionToJoin = InviteResult;
				DestroySession();
			}
		}
	}
}

void UEOSGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (bIsLoggedIn)
	{
		if (OnlineSubsystem)
		{
			if (IOnlineSessionPtr SessionPtr = OnlineSubsystem->GetSessionInterface())
			{
				FString ConnectionInfo = FString();
				SessionPtr->GetResolvedConnectString(SessionName, ConnectionInfo);
				if (!ConnectionInfo.IsEmpty())
				{
					if (MenuController)
					{
						MenuController->ClientTravel(ConnectionInfo, ETravelType::TRAVEL_Absolute);
					}
				}
			}
		}
	}
}

void UEOSGameInstance::SetName(FString NewName)
{
	if (!NameSet)
	{
		PlayerName = NewName;
		if (bIsLoggedIn)
		{
			NameSet = true;
		}
	}
}

void UEOSGameInstance::SetMenuController(AMenuController* NewController)
{
	MenuController = NewController;
}

void UEOSGameInstance::AddNewNotification(UUINotification* NewNotification)
{
	Notifications.Emplace(NewNotification);
	UpdateNotificationUI();
}

FString UEOSGameInstance::GetChoppedNetId(FString Original)
{
	int32 PipePosition = -1;
	if (Original.FindChar('|', PipePosition))
	{
		FString StrChopped = Original.LeftChop(PipePosition + 1);
		return StrChopped;
	}
	return Original;
}
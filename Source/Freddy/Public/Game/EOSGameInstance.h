// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "EOSGameInstance.generated.h"

/** Whether the build is for developer or player */
UENUM(BlueprintType)
enum EInviteResponse
{
	Accept,
	Invite,
	Ignore
};

/** Whether the build is for developer or player */
UENUM()
enum EGameType
{
	Developer,
	Player
};

enum EOnJoinSessionCompleteResult::Type;

/**
 * Game instance that implements Epic Online Subsystem
 */
UCLASS()
class FREDDY_API UEOSGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	/** Sets default values */
	UEOSGameInstance();

	/** Called when the game instance starts */
	virtual void Init() override;

	/** Called to log player into Epic account */
	UFUNCTION(BlueprintCallable)
	void Login();

	/** Called when a player logs in */
	void OnLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error);

	/** Creates a new online session */
	UFUNCTION(BlueprintCallable)
	void CreateSession();

	/** Called when a session is created */
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

	/** Destroyes the online session*/
	UFUNCTION(BlueprintCallable)
	void DestroySession();

	/** Called when a session is destroyed */
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);

	/** Gets all friends from friends list */
	UFUNCTION(BlueprintCallable)
	void GetAllFriends();

	/** Called when all friends are retrieved from friends list */
	void OnGetAllFriendsComplete(int32 LocalUserNum, bool bWasSuccessful, const FString& ListName, const FString& ErrorStr);

	/** Invites friend to session */
	UFUNCTION(BlueprintCallable)
	void InviteFriendToSession(int FriendIndex);

	/** Accepts invite from friends list */
	UFUNCTION(BlueprintCallable)
	void AcceptFriendInvite(int FriendIndex);

	/** Called when session invite is received */
	void OnSessionInviteReceived(const FUniqueNetId& UserId, const FUniqueNetId& FromId, const FString& AppId, const FOnlineSessionSearchResult& InviteResult);

	/** Called when session invite is received */
	void OnSessionUserInviteAccepted(const bool bWasSuccess, const int32 ControllerId, TSharedPtr<const FUniqueNetId> UserId, const FOnlineSessionSearchResult& InviteResult);

	/** Called when session invite is received */
	void OnQueryUserInfoComplete(int32 LocalUserNum, bool bWasSuccessful, const TArray<FUniqueNetIdRef>& UserIds, const FString& ErrorStr);

	/** Joins the found session */
	void StartJoinSession(const FOnlineSessionSearchResult* InviteResult);

	/** Called when a session has been successfully joined */
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	/** Responds to invite from friend */
	UFUNCTION(BlueprintCallable)
	void RespondToInvite(FString FromIdStr, EInviteResponse InviteResponse);

	/** Sets player name to specified value */
	void SetName(FString NewName);

	/** Sets player name to specified value */
	void SetMenuController(class AMenuController* NewController);

protected:
	/** Adds new notification and sends it to the container */
	void AddNewNotification(class UUINotification* NewNotification);

	/** Adds new notification and sends it to the container */
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateNotificationUI();

	/** Returns the part of the NetId string to the left of the | character */
	FString GetChoppedNetId(FString Original);

public:
	/** List of all read friends */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class UFriendInfo*> Friends;

	/** List of all pending invitations */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class UInviteInfo*> Invites;

	/** List of all notifications */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UUINotification*> Notifications;

	/** Whether the friend's list has ever been read */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bFriendsListInitiallyRead;

	/** Name of the player from game start */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString PlayerName;

	/** Whether the player name has been set */
	bool NameSet;

protected:
	/** Reference to online subsystem */
	class IOnlineSubsystem* OnlineSubsystem;

	/** Whether the player is logged in */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsLoggedIn;

	/** What type of game this game instance is */
	EGameType GameType;

	/** Reference to owning controller */
	class ALoadingController* LoadingController;

	/** Reference to owning controller */
	class AMenuController* MenuController;

	/** Reference to owning controller */
	const class FOnlineSessionSearchResult* SessionToJoin;
};

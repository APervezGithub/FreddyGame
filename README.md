# FreddyGame
Currently in progress horror game

Contains a lobby and party system made with Epic Online Services. You can view your friends list and invite players, who will receive an invitation through the overlay and one that appears in game. Accepting either invitation will add you to the party's lobby session, from where the host can server travel to the level

Most of the EOS functionality is in the EOSGameInstance class, as well as a slight modification to the OnlineSessionEOS class in the OnlineSubsystemEOS plugin that allows receiving of Session Invites

Also has an improved version of the networked interaction system that allows implementing all functions in Blueprints as well as C++

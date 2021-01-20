# network-priveleges
Plugin for Unreal Engine 4 that enables role-based authorization. Particularly useful for things such as chat/server commands.

# How it works
Unreal Engine's default configuration for the way player sessions are replicated from server to client guarantees that each connected player will be trasmitted ONLY the PlayerController object that they "own", A.K.A. the object that represents the player's intentions in the game.
Players are not authorized to (and their clients do not) receive instances of other players' player controllers. A client can only communicate with the game authority (the server in this context) about the single player controller it has been given.
In this way, player controllers can act in the way an enterprise full-stack developer may think of API roles, or as envelopes for multiple roles.

#pragma once

namespace memory
{
	uintptr_t find_dma_addy(uintptr_t ptr, std::vector<unsigned int> offsets);
}

namespace offsets
{
	inline uintptr_t dwLocalPlayer = 0xDA5A84; // GameAssembly.dll
	inline uintptr_t dwCharacter = 0xDAF3E8; // GameAssembly.dll
	inline std::vector<unsigned int> dwCharacterState = { 0x5C, 0x20, 0x34, 0x28 }; // CREW = 0, IMP = 1; GHOST = 257 | dwCharacter
	inline uintptr_t dwEnvironment = 0x12A86E0; // UnityPlayer.dll
	inline std::vector<unsigned int> dwWallCheck = { 0x80, 0x5C, 0x0 }; // ON = 1, OFF = 2 | dwEnvironment
	inline std::vector<unsigned int> dwOriginX = { 0x80, 0x5C, 0x2C }; // dwEnvironment
	inline std::vector<unsigned int> dwOriginY = { 0x80, 0x5C, 0x30 }; // dwEnvironment

	// Player
	inline std::vector<unsigned int> dwPlayerId = { 0x5C, 0x0, 0x34, 0x8, 0x0 }; // dwLocalPlayer
	inline std::vector<unsigned int> flSpeed = { 0x5C, 0x4, 0x14 }; // dwLocalPlayer
	inline std::vector<unsigned int> dwColorId = { 0x5C, 0x0, 0x34, 0x10 }; // dwLocalPlayer
	inline std::vector<unsigned int> btIsDead = { 0x5C, 0x0, 0x34, 0x29 }; // dwLocalPlayer
	inline std::vector<unsigned int> btIsImpostor = { 0x5C, 0x0, 0x34, 0x8 }; // dwLocalPlayer / buggly
	inline std::vector<unsigned int> strPlayerName = { 0x5C, 0x0, 0x34, 0xC, 0xC }; // dwLocalPlayer | Unicode
	inline std::vector<unsigned int> flLightRadius = { 0x5C, 0x0, 0x54, 0x1C }; // dwLocalPlayer
	// Server Info
	inline uintptr_t dwServerManager = 0x00DA5A84; // GameAssembly.dll
	inline std::vector<unsigned int> dwMaxPlayer = { 0x5C, 0x4, 0x8 }; // dwServerManager
	inline std::vector<unsigned int> btMapId = { 0x5C, 0x4, 0x10 }; // dwServerManager

	// Time
	inline std::vector<unsigned int> dwDiscussionTime = { 0x5C, 0x4, 0x44 }; // dwLocalPlayer
	inline std::vector<unsigned int> dwVotingTime = { 0x5C, 0x4, 0x48 }; // dwLocalPlayer

	// Crew
	inline std::vector<unsigned int> dwEmergencyCount = { 0x5C, 0x4, 0x30 }; // dwLocalPlayer
	inline std::vector<unsigned int> dwRemainingEmergencyCount = { 0x5C, 0x0, 0x48 }; // dwLocalPlayer
	inline std::vector<unsigned int> flCrewLightDistance = { 0x5C, 0x4, 0x18 }; // dwLocalPlayer
	inline std::vector<unsigned int> dwMaxReportDistance = { 0x5C, 0x0, 0x2C }; // dwLocalPlayer

	// Impostor
	inline std::vector<unsigned int> dwImposterCount = { 0x5C, 0x4, 0x38 }; // dwLocalPlayer
	inline std::vector<unsigned int> flImpostorLightDistance = { 0x5C, 0x4, 0x1C }; // dwLocalPlayer
	inline std::vector<unsigned int> dwKillCooldown = { 0x5C, 0x4, 0x20 }; // dwLocalPlayer
	inline std::vector<unsigned int> dwKillDistance = { 0x5C, 0x4, 0x40 }; // dwLocalPlayer | Short = 1, Normal = 2, Far = 3
	inline 	std::vector<unsigned int> dwKillTimer = { 0x5C, 0x0, 0x44 }; // dwLocalPlayer
};
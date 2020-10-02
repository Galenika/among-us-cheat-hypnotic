#pragma once

struct Settings
{
	/* Our master switch for our cheat. This will cause no crashes since pointers will return null before you're inside a lobby.*/
	bool CheatEnabled;

	struct
	{
		bool AlwaysImposter;
		bool Speed;
		bool NoKillCoolDown;
		bool ChangeKillDistance;
		int KillDistance;
		int SpeedValue = 1;
	} local;

	struct
	{
		bool InstantVoteSkip;
		bool ChangeColor;
		int ColorID;
		bool CrewmateVisionModifier;
		int CrewmateVisionInterval;
	} server;
};

namespace menu
{
	extern Settings settings;
	bool is_opened();
	void custom_colors();
	bool tabs(std::vector<const char*> tabs);

	/* menu functions */
	void render();

	/* menu variables */
	inline bool opened = false;

	struct Info
	{
		int tab_value = 0;
	}; inline Info info;

	/* shitty settings system */
	static void load_settings()
	{
		CreateDirectory(L"settings", NULL);
		std::string chars;
		chars = "settings/";
		chars += "settings";
		chars += ".hook";
		std::ifstream f(chars.c_str());
		if (!f.good()) return;

		FILE* fin = fopen(chars.c_str(), "r");
		fread(&settings, sizeof(Settings), 1, fin);
		fclose(fin);
	}

	static void save_settings()
	{
		CreateDirectory(L"settings", NULL);
		std::string chars;
		chars = "settings/";
		chars += "settings";
		chars += ".hook";
		FILE* fout = fopen(chars.c_str(), "w");
		fwrite(&settings, sizeof(Settings), 1, fout);
		fclose(fout);
	}
}
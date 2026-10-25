#include "pch.h"
#include "EditSrv.h"

// EXCEPTION CLASS ******************

edit::EXCEPTION::EXCEPTION(int what_happened)
{
	what = what_happened;
}

const wchar_t* edit::EXCEPTION::eGet()
{
	switch (what)
	{
	case BAD_INDEX:
		return L"Bad index passed to a BAG method !";

	case BAD_ITERATOR:
		return L"Bad iterator passed to a BAG member !";

	case BAD_PARAM:
		return L"Bad parameter passed to a BAG method !";

	case BAD_PTR:
		return L"Bad pointer passed to a BAG method !";

	case BAD_MEMORY:
		return L"Out of memory error while constructing BAG instance !";
	}

	return L"Unlisted error occurred in a BAG container !";
}

/////////////////////////////////////

// RANDIT CLASS *********************

edit::RANDIT::RANDIT()
{
	std::random_device rd{};
	std::seed_seq sq{ rd(),rd(), rd(), rd(), rd(), rd(), rd(), rd() };

	twister = new std::mt19937(sq);
}

edit::RANDIT::~RANDIT()
{
	if (twister)delete twister;
}

int edit::RANDIT::operator()(int min, int max)
{
	if (max < min)return -1;

	std::uniform_int_distribution distr(min, max);

	return distr(*twister);
}
float edit::RANDIT::operator()(float min, float max)
{
	if (max < min)return -1.0f;

	std::uniform_real_distribution<float> distr(min, max);

	return distr(*twister);
}

////////////////////////////////////


// FUNCTIONS **************************

int edit::CodeChar(wchar_t symbol, int code)
{
	int coded{ static_cast<int>(symbol) };

	coded += code;

	return coded;
}
wchar_t edit::DecodeChar(int symbol, int code)
{
	symbol -= code;

	return static_cast<wchar_t>(symbol);
}
bool edit::FileExist(const wchar_t* name)
{
	std::wifstream test{ name };

	return test.good();
}

size_t edit::SaveFile(const wchar_t* name, BAG<wchar_t>& Bag, int code, bool append)
{
	size_t chars_saved = Bag.size();

	if (Bag.empty())return chars_saved;

	if (append)
	{
		std::wofstream save(name, std::ios::app);
		
		save << Bag.size() << std::endl;
		save << code << std::endl;

		for (size_t i = 0; i < Bag.size(); ++i)
		{
			int letter = CodeChar(Bag[i], code);
			save << letter << std::endl;
		}
		save.close();
	}
	else
	{
		std::wofstream save(name);

		save << Bag.size() << std::endl;
		save << code << std::endl;

		for (size_t i = 0; i < Bag.size(); ++i)
		{
			int letter = CodeChar(Bag[i], code);
			save << letter << std::endl;
		}
		save.close();
	}

	return chars_saved;
}
bool edit::LoadFile(const wchar_t* name, BAG<wchar_t>& Bag)
{
	if (!FileExist(name))return false;

	int bag_size{ 0 };
	int code{ 0 };

	std::wifstream load(name);

	load >> bag_size;
	load >> code;

	Bag.clear();

	for (size_t i = 0; i < bag_size; ++i)
	{
		int letter = 0;

		load >> letter;
		Bag.push_back(DecodeChar(letter, code));
	}

	return true;
}
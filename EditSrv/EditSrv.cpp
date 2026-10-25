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
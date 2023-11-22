//maker
#include "../../Maker/inc/Maker.hpp"

void setup_dlls(Maker& maker)
{
	maker.m_path_dll.clear();
	maker.m_path_dll.push_back(maker.m_edll + "liblapack.dll");
}
void setup_libs(Maker& maker)
{
	maker.m_libs.clear();
	maker.m_libs += maker.m_elib + "liblapack.lib ";
	maker.m_libs += "../Math/dist/" + maker.m_mode + "/Math.lib ";
}
int main(int argc, char** argv)
{
	//setup
	Maker maker;
	maker.m_lib = true;
	maker.m_out = "rigid";
	maker.setup(argc, argv);
	maker.m_incs += "/I ../Math/ ";
	//build
	if(!maker.m_clean)
	{
		setup_libs(maker);
		setup_dlls(maker);
		maker.build_src();
		maker.build_exe();
		maker.build_run();
	}
	if(maker.m_clean)
	{
		maker.build_clean();
	}
	//return
	return EXIT_SUCCESS;
}
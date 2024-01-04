//maker
#include "../../Maker/inc/Maker.hpp"

void setup_dlls(Maker& maker)
{
	maker.m_path_dll.clear();
	maker.m_path_dll.push_back(maker.m_edll + "glew32.dll");
	maker.m_path_dll.push_back(maker.m_edll + "libblas.dll");
	maker.m_path_dll.push_back(maker.m_edll + "freeglut.dll");
	maker.m_path_dll.push_back(maker.m_edll + "freetype.dll");
	maker.m_path_dll.push_back(maker.m_edll + "liblapack.dll");
	maker.m_path_dll.push_back(maker.m_edll + "libgfortran-3.dll");
	maker.m_path_dll.push_back(maker.m_edll + "libquadmath-0.dll");
	maker.m_path_dll.push_back(maker.m_edll + "libgcc_s_sjlj-1.dll");
}
void setup_libs(Maker& maker)
{
	maker.m_libs.clear();
	maker.m_libs += maker.m_elib + "glew32.lib ";
	maker.m_libs += maker.m_elib + "freeglut.lib ";
	maker.m_libs += maker.m_elib + "freetype.lib ";
	maker.m_libs += maker.m_elib + "liblapack.lib ";
	maker.m_libs += "../Math/dist/" + maker.m_mode + "/libmath.lib ";
	maker.m_libs += "../Canvas/lib/dist/" + maker.m_mode + "/libcanvas.lib ";
}
void build_math(Maker& maker)
{
	std::filesystem::current_path("../Math");
	if(system(maker.m_mode.compare("debug") == 0 ? "make.exe" : "make.exe m=r"))
	{
		fprintf(stderr, "Error building math!\n");
		exit(EXIT_FAILURE);
	}
	std::filesystem::current_path("../rigid-body");
}
void build_canvas(Maker& maker)
{
	std::filesystem::current_path("../Canvas/lib");
	if(system(maker.m_mode.compare("debug") == 0 ? "make.exe" : "make.exe m=r"))
	{
		fprintf(stderr, "Error building canvas!\n");
		exit(EXIT_FAILURE);
	}
	std::filesystem::current_path("../../rigid-body");
}

int main(int argc, char** argv)
{
	//setup
	Maker maker;
	maker.m_lib = true;
	maker.m_out = "rigid";
	maker.setup(argc, argv);
	maker.m_incs += "/I .. /I ../Math/ ";
	//build
	if(!maker.m_clean)
	{
		setup_libs(maker);
		setup_dlls(maker);
		build_math(maker);
		build_canvas(maker);
		maker.build_src();
		maker.build_dll();
		maker.build_exe();
		maker.build_run();
		maker.build_debug();
	}
	if(maker.m_clean)
	{
		maker.build_clean();
	}
	//return
	return EXIT_SUCCESS;
}
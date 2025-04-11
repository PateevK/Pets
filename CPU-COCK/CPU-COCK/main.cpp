#include <iostream>
#include <chrono>
#include <thread>
#include <bitset>
#include <windows.h>
#include "include/libcpuid.h"
#include "CPU-C/core.h"
#include "CPU-C/Tool/Displayer.h"

// I did structs /ref struct Processor_infoblock /ref struct Total_infoblock.
// 
// 1.Find a way to fill the structs.
// Maybe refactor them.
//
// TODO:
// 1. /file: core.cpp /line: 22 /com: iterate m_error_array and match with matchtable.
// 
// 2. /struct Processor_infoblock::name & specification are the same;
// 
// 4. Fix overall optimization like unnessesary copiyng of string, vectors, etc..
//
// 5. Handle hypervisors.
// 
// 6. Fill /file core.h /struct Footer_infoblock m_foot_block = {};
//
// 7. ARM architecture is not supported.
// 
// 8. Fill /file core.cpp /func void CPU_info::FillProcessorInfoBlock()  
//	max_tdp, max_voltage, technology_nm, package.
// 
// 10. /file cope.cpp /line 22 m_proc_block_array.reserve(m_sys_id.num_cpu_types);
//           // Do need this to be a vector ?
// 
// 11. The Cache General option is unavailable.
//
// 9. Fill clocks. !!!!!!!!
// 
// 12. I can add option to choose the function values /func cpu_clock_by_ic(200, 4)
// 
// 13. WMIreader doesn't have error handler; 
//
// 14. Make updatable core load display. 
// 
// 15. Automate OpenHardwareMonitor opening.



int main() {

	CPU_info cpu_info;
	Displayer::DisplayAllInfo(cpu_info);

	std::cout << '\n' << cpuid_error();
	std::cout << '\n' << "END";
	std::cin.get();
return 0;
}

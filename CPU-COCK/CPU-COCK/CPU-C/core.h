#pragma once
#include <iostream>
#include "..\Include\libcpuid.h"
#include "logger.h"
#include "structs.h"
//#include "WMI_reader\WMIreader.h"

class CPU_info {
public:
	CPU_info() {
		InitLibcpuid();

		FillProcessorInfoBlock();
		FillCacheInfoBlock();
		//FillCoreInfoBlock();
		FillFooterInfoBlock();
	}
	~CPU_info() {
		cpuid_free_raw_data_array(&m_raw_data);
		cpuid_free_system_id(&m_sys_id);
	}
	// One infoblock per core type.
	//See: /file core.cpp /line 21 -  m_proc_block_array.reserve(m_sys_id.num_cpu_types); 
	std::vector<Processor_infoblock> m_proc_block_array = {};  
	std::vector<Cache_infoblock> m_cache_infoblock_array = {}; // Per cpu type + 1 general.
	std::vector<Core_infoblock> m_core_infoblock_array = {}; // One per core num + 1 general.
	Footer_infoblock m_foot_block;
	std::vector<error_t> m_error_array;

private:
	int InitLibcpuid();
	void FillProcessorInfoBlock();
	void FillCacheInfoBlock();
	int ValidataCache(int result);
	void FillCoreInfoBlock();
	void FillFooterInfoBlock();

	system_id_t m_sys_id = {};
	cpu_raw_data_array_t m_raw_data = {};
	bool m_error_flag = 0;
};



////std::cout << cpuid_get_total_cpus() << '\n';
//std::cout << "Type0:\n";
//std::cout << "Cache size KB:: " << m_sys_id.cpu_types[0].l1_data_cache << '\n'; //KB
//std::cout << "Cache instances:: " << m_sys_id.cpu_types[0].l1_data_instances << '\n';
//std::cout << "Cache line size Bytes::" << m_sys_id.cpu_types[0].l1_data_cacheline << '\n'; // Bytes
//std::cout << "Cache associativity:: " << m_sys_id.cpu_types[0].l1_data_assoc << '\n';

//std::cout << "Type1:\n";
//std::cout << "Cache size KB:: " << m_sys_id.cpu_types[1].l1_data_cache << '\n'; //KB
//std::cout << "Cache instances:: " << m_sys_id.cpu_types[1].l1_data_instances << '\n';
//std::cout << "Cache line size Bytes::" << m_sys_id.cpu_types[1].l1_data_cacheline << '\n'; // Bytes
//std::cout << "Cache associativity:: " << m_sys_id.cpu_types[1].l1_data_assoc << '\n';



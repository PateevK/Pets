#pragma once
#include <iostream>
#include "..\core.h"


namespace Displayer {
	void DisplayProcessor_infoblock(const Processor_infoblock& proc) {
		std::cout << "Name" << "           | " << proc.name << "  " << '\n';
		std::cout << "Code name" << "      | " << proc.code_name << "  " << '\n';
		std::cout << "Name" << "           | " << proc.package << "  " << std::endl;
		std::cout << "Max.TDP" << "        | " << proc.max_tdp << "  " << '\n';
		std::cout << "Max.Vol." << "       | " << proc.max_voltage << "  " << '\n';
		std::cout << "Tech" << "           | " << proc.technology_nm << "  " << '\n';
		std::cout << "Specification" << "  | " << proc.specification << "  " << '\n';
		std::cout << "Family" << "         | " << proc.family << "  " << '\n';
		std::cout << "Model" << "          | " << proc.model << "  " << '\n';
		std::cout << "Stepping" << "       | " << proc.stepping << "  " << '\n';
		std::cout << "Architecture " << "  | " << proc.arch << " " << '\n';
		std::cout << "Ext. Family" << "    | " << proc.ext_family << "  " << '\n';
		std::cout << "Ext. model" << "     | " << proc.ext_model << "  " << '\n';
		std::cout << "Feature level" << "  | " << proc.feat_level << "  " << '\n';
		std::cout << "?????" << "          | " << "?????" << "  " << '\n';
	}

	void DispalyCache_infoblock(const Cache_infoblock& cache) {
		std::cout << "Core type - " << cache.core_type << " : " << std::endl;
		if (cache.l1_cache_instances != 0) {
			std::cout << "Cache L1 | " << cache.l1_cache_instances <<
				" x " << cache.l1_cache_size_kb << " KB * " << cache.l1_cache_associativity << " - way * "
				<< cache.l1_cacheline_size_bytes << " B " << std::endl;
		}
		else std::cout << "Cache L1 | Processor doesn't have L1 cache \n";
		if (cache.l2_cache_instances != 0) {
			std::cout << "Cache L2 | " << cache.l2_cache_instances <<
				" x " << cache.l2_cache_size_kb << " KB * " << cache.l2_cache_associativity << " - way * "
				<< cache.l2_cacheline_size_bytes << " B " << std::endl;
		}
		else std::cout << "Cache L2 | Processor doesn't have L2 cache \n";
		if (cache.l3_cache_instances != 0) {
			std::cout << "Cache L3 | " << cache.l3_cache_instances <<
				" x " << cache.l3_cache_size_kb << " KB * " << cache.l3_cache_associativity << " - way * "
				<< cache.l3_cacheline_size_bytes << " B " << std::endl;
		}
		else std::cout << "Cache L3 | Processor doesn't have L3 cache \n";
		if (cache.l4_cache_instances != 0) {
			std::cout << "Cache L4 | " << cache.l4_cache_instances <<
				" x " << cache.l4_cache_size_kb << " KB * " << cache.l4_cache_associativity << " - way * "
				<< cache.l4_cacheline_size_bytes << " B " << std::endl;
		}
		else std::cout << "Cache L4 | Processor doesn't have L4 cache \n";
	}

	void DisplayFooter_infoblock(const Footer_infoblock& foot) {
		std::cout << "-- Total processors - " << foot.tot_num_processors << " | " << "Threads - " << foot.tot_num_logical << " | " << "Cores - " << foot.tot_num_cores;
		for (int i = 0;i < foot.vec_type_num.size(); i++) {
			std::cout << " | " << foot.vec_type_num[i].num << (char)((foot.vec_type_num[i].type[0]) - 32);
		}
		std::cout << " | --";
		std::cout << std::endl;
	}

	void DisplayAllInfo(const CPU_info& cpu_info) {

		DisplayFooter_infoblock(cpu_info.m_foot_block);
		std::cout << "----------------------\n";

		for (int i = 0; i < cpu_info.m_proc_block_array.size(); i++) {
			std::cout << "PROCESSOR #" << i << " : " << '\n';
			DisplayProcessor_infoblock(cpu_info.m_proc_block_array[i]);
		}
		std::cout << "----------------------\n";
		//
		for (int i = 0; i < cpu_info.m_cache_infoblock_array.size(); i++) {
			DispalyCache_infoblock(cpu_info.m_cache_infoblock_array[i]);
		}
		std::cout << "----------------------\n";
		//
		for (int i = 0; i < cpu_info.m_core_infoblock_array.size(); i++) {
			//DisplayCore_infoblock(cpu_info.m_core_infoblock_array[i]);
		}
	}
}
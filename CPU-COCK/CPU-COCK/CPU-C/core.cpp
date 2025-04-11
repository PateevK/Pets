#include "core.h"

int CPU_info::InitLibcpuid() {
	if (!cpuid_present()) {
		PRINT_ERR("ERROR_NO_CPUID")
		m_error_array.push_back(ERROR_NO_CPUID);
		m_error_flag = 1;
		return ERROR_NO_CPUID;
	}
	if (cpuid_get_all_raw_data(&m_raw_data) < 0 || cpu_identify_all(&m_raw_data, &m_sys_id) < 0) {
		m_error_array.push_back(ERROR_FAIL_CPUID);
		PRINT_ERR("ERROR_FAIL_CPUID")
		m_error_flag = 1;
		return ERROR_FAIL_CPUID;
	}
	if (m_sys_id.num_cpu_types <= 0) {
		m_error_array.push_back(ERROR_NO_CPUTYPE);
		PRINT_ERR("ERROR_NO_CPUTYPE")
		return ERROR_NO_CPUTYPE;
	}
	m_proc_block_array.reserve(m_sys_id.num_cpu_types); // Do need this to be a vector ?
	m_cache_infoblock_array.reserve(m_sys_id.num_cpu_types + 1);
	// Handle MSR

}


void CPU_info::FillProcessorInfoBlock() {
	cpu_id_t cpuid;
	Processor_infoblock procInfo;
	if (m_error_flag = 1) {}                //iterate m_error_array and match with matchtable
    cpuid = m_sys_id.cpu_types[0];

	//Fill core_type
	procInfo.core_type = cpu_purpose_str(cpuid.purpose);
	//Fill name
	procInfo.name = cpuid.brand_str; 
	//Fill code name 
	procInfo.code_name = cpuid.cpu_codename;
	//Fill package
	procInfo.package = "***";   // figure out a way to fill /structure Processor_infoblock::package,
	//Fill specification  
	procInfo.specification = cpuid.brand_str;
	//Fill max_tdp
	procInfo.max_tdp = "***";
	//Fill  max_voltage
	procInfo.max_voltage = "***";
	//Fill technology_nm
	procInfo.technology_nm = "***";
	//Fill family
	procInfo.family = std::to_string(cpuid.x86.family);
	//Fill model
	procInfo.model = std::to_string(cpuid.x86.model);
	//Fill stepping
	procInfo.stepping = std::to_string(cpuid.x86.stepping);
	//Fill ext_family 
	procInfo.ext_family = std::to_string(cpuid.x86.ext_family);
	//Fill ext_model
	procInfo.ext_model = std::to_string(cpuid.x86.ext_model);
	//Fill arch
	procInfo.arch = cpu_architecture_str(cpuid.architecture);
	//Fill feat_level
	procInfo.feat_level = cpu_feature_level_str(cpuid.feature_level);

	m_proc_block_array.emplace_back(procInfo);
}

int CPU_info::ValidataCache(int res) {
	if (res <= 0) {
		m_error_array.push_back(ERROR_FAIL_CACHE);
		PRINT_ERR("ERROR_FAIL_CACHE")
		return ERROR_FAIL_CACHE;
	}
	return res;
}

void CPU_info::FillCacheInfoBlock() {
	Cache_infoblock cacheinf;

	for (int i = 0; i < m_sys_id.num_cpu_types; i++) {
		cpu_id_t cpuid = m_sys_id.cpu_types[i];

		cacheinf.core_type = cpu_purpose_str(cpuid.purpose);

		cacheinf.l1_cache_size_kb = ValidataCache(cpuid.l1_data_cache);
		cacheinf.l1_cache_instances = cpuid.l1_data_instances;
		cacheinf.l1_cacheline_size_bytes = cpuid.l1_data_cacheline;
		cacheinf.l1_cache_associativity = cpuid.l1_data_assoc;

		cacheinf.l2_cache_size_kb = ValidataCache(cpuid.l2_cache);
		cacheinf.l2_cache_instances = cpuid.l2_instances;
		cacheinf.l2_cacheline_size_bytes = cpuid.l2_cacheline;
		cacheinf.l2_cache_associativity = cpuid.l2_assoc;

		cacheinf.l3_cache_size_kb = ValidataCache(cpuid.l3_cache);
		cacheinf.l3_cache_instances = cpuid.l3_instances;
		cacheinf.l3_cacheline_size_bytes = cpuid.l3_cacheline;
		cacheinf.l3_cache_associativity = cpuid.l3_assoc;

		cacheinf.l4_cache_size_kb = ValidataCache(cpuid.l4_cache);
		cacheinf.l4_cache_instances = cpuid.l4_instances;
		cacheinf.l4_cacheline_size_bytes = cpuid.l4_cacheline;
		cacheinf.l4_cache_associativity = cpuid.l4_assoc;

		m_cache_infoblock_array.emplace_back(cacheinf);
	}
}


//int GetNumCores(WMIreader& reader) {
//
//	reader.Query(R"(SELECT * FROM Sensor WHERE Name LIKE "CPU core #%")");
//	std::vector<std::wstring> vec = reader.GetProperty<std::wstring>(L"Name");
//	int count = 0;
//	for (const auto& i : vec) {
//		count++;
//	}
//	return count - 1; // For convenience it should begin from 0.
//}

//void CPU_info::FillCoreInfoBlock() {
//	//to open HardwareMonitor();
//	WMIreader reader(L"ROOT\\OpenHardwareMonitor");
//	int numCores = GetNumCores(reader);
//	m_core_infoblock_array.reserve(numCores);
//	Core_infoblock core_infoblock;
//	for (int i = 0; i < numCores; i++) {
//		core_infoblock.core_num = i;
//		core_infoblock.core_load = 0;
//		m_core_infoblock_array.emplace_back(core_infoblock);
//	}
//}

void CPU_info::FillFooterInfoBlock() {
	for (int i = 0; i < m_cache_infoblock_array.size(); i++) {
		std::string type = {0};
		if (type != m_cache_infoblock_array[i].core_type) {
			type = m_cache_infoblock_array[i].core_type;
			int num = m_cache_infoblock_array[i].l1_cache_instances;
			m_foot_block.vec_type_num.push_back({ type, num });
			m_foot_block.tot_num_cores += num;
		}
		else continue;
	}
	m_foot_block.tot_num_processors = m_proc_block_array.size();
	m_foot_block.tot_num_logical = cpuid_get_total_cpus();
}

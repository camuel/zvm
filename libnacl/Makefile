#RELEASE BUILD
#CCFLAGS=-DNDEBUG -O2
#CXXFLAGS=-DNDEBUG -O2

#DEBUG BUILD
CCFLAGS=-DDEBUG -g
CXXFLAGS=-DDEBUG -g

CCFLAGS0=-c -m64 -D_FORTIFY_SOURCE=2 -DNACL_WINDOWS=0 -DNACL_OSX=0 -DNACL_LINUX=1 -D_BSD_SOURCE=1 -D_POSIX_C_SOURCE=199506 -D_XOPEN_SOURCE=600 -D_GNU_SOURCE=1 -D_LARGEFILE64_SOURCE=1 -D__STDC_LIMIT_MACROS=1 -D__STDC_FORMAT_MACROS=1 -DNACL_BLOCK_SHIFT=5 -DNACL_BLOCK_SIZE=32 -DNACL_BUILD_ARCH=x86 -DNACL_BUILD_SUBARCH=64 -DNACL_TARGET_ARCH=x86 -DNACL_TARGET_SUBARCH=64 -DNACL_STANDALONE=1 -DNACL_ENABLE_TMPFS_REDIRECT_VAR=0 -I.
CCFLAGS1=-std=gnu99 -Wdeclaration-after-statement -fPIE -Wall -pedantic -Wno-long-long -fvisibility=hidden -fstack-protector --param ssp-buffer-size=4
CCFLAGS2=-Wextra -Wswitch-enum -Wsign-compare
CCFLAGS3=-fno-strict-aliasing -Wno-missing-field-initializers
CCFLAGS4=-DNACL_TRUSTED_BUT_NOT_TCB
CXXFLAGS1=-c -std=c++98 -Wno-variadic-macros -m64 -fPIE -Wall -pedantic -Wno-long-long -fvisibility=hidden -fstack-protector --param ssp-buffer-size=4 -DNACL_TRUSTED_BUT_NOT_TCB -D_FORTIFY_SOURCE=2 -DNACL_WINDOWS=0 -DNACL_OSX=0 -DNACL_LINUX=1 -D_BSD_SOURCE=1 -D_POSIX_C_SOURCE=199506 -D_XOPEN_SOURCE=600 -D_GNU_SOURCE=1 -D_LARGEFILE64_SOURCE=1 -D__STDC_LIMIT_MACROS=1 -D__STDC_FORMAT_MACROS=1 -DNACL_BLOCK_SHIFT=5 -DNACL_BLOCK_SIZE=32 -DNACL_BUILD_ARCH=x86 -DNACL_BUILD_SUBARCH=64 -DNACL_TARGET_ARCH=x86 -DNACL_TARGET_SUBARCH=64 -DNACL_STANDALONE=1 -DNACL_ENABLE_TMPFS_REDIRECT_VAR=0 -I.
CXXFLAGS2=-Wl,-z,noexecstack -m64 -Wno-variadic-macros -L/usr/lib64 -pie -Wl,-z,relro -Wl,-z,now -Wl,-rpath=obj

all: libnacl tests

libnacl: obj/libnacl_fault_inject.a obj/libnacl_platform_qualify.a obj/libnacl_validate_x86_64.a obj/libnacl_validate_reg_sfi_x86_64.a obj/libnacl_copy_x86_64.a obj/libnacl_decoder_x86_64.a obj/libnacl_opcode_modeling_x86_64.a obj/libnacl_validate_base_x86_64.a obj/libnacl_platform.a obj/libnacl_gio.a

tests: test_compile
	test/x86_validator_tests_nc_remaining_memory
	test/x86_decoder_tests_nc_inst_state
	test/x86_validator_tests_halt_trim
	test/x86_validator_tests_nc_inst_bytes

test_compile: test/x86_validator_tests_halt_trim test/x86_decoder_tests_nc_inst_state test/x86_validator_tests_nc_inst_bytes test/x86_validator_tests_nc_remaining_memory #test/manifest_parser_test

obj/halt_trim_tests.o: src/validator/x86/halt_trim_tests.cc
	g++ ${CXXFLAGS} -o obj/halt_trim_tests.o ${CXXFLAGS1} -Igtest/include src/validator/x86/halt_trim_tests.cc

test/x86_validator_tests_halt_trim: obj/halt_trim_tests.o obj/libnacl_validate_x86_64.a obj/libnacl_validate_reg_sfi_x86_64.a obj/libnacl_copy_x86_64.a obj/libnacl_decoder_x86_64.a obj/libnacl_opcode_modeling_x86_64.a obj/libnacl_validate_base_x86_64.a obj/libnacl_platform.a obj/libnacl_gio.a
	g++ ${CXXFLAGS} -o test/x86_validator_tests_halt_trim ${CXXFLAGS2} obj/halt_trim_tests.o -L/usr/lib -Llib -Lgtest -lgtest -lnacl_validate_base_x86_64 -lnacl_validate_x86_64 -lnacl_validate_reg_sfi_x86_64 -lnacl_copy_x86_64 -lnacl_decoder_x86_64 -lnacl_opcode_modeling_x86_64 -lnacl_platform -lnacl_gio -lrt -lpthread -lcrypto

obj/nc_inst_state_tests.o: src/validator/x86/decoder/nc_inst_state_tests.cc
	g++ ${CXXFLAGS} -o obj/nc_inst_state_tests.o ${CXXFLAGS1} -Igtest/include src/validator/x86/decoder/nc_inst_state_tests.cc

test/x86_decoder_tests_nc_inst_state: obj/nc_inst_state_tests.o obj/ncval_decode_tables.o obj/libnacl_copy_x86_64.a obj/libnacl_decoder_x86_64.a obj/libnacl_opcode_modeling_x86_64.a obj/libnacl_validate_base_x86_64.a obj/libnacl_platform.a obj/libnacl_gio.a
	g++ ${CXXFLAGS} -o test/x86_decoder_tests_nc_inst_state ${CXXFLAGS2} obj/nc_inst_state_tests.o -L/usr/lib -Llib -Lgtest -lgtest -lnacl_validate_base_x86_64 -lnacl_validate_x86_64 -lnacl_validate_reg_sfi_x86_64 -lnacl_copy_x86_64 -lnacl_decoder_x86_64 -lnacl_opcode_modeling_x86_64 -lnacl_platform -lnacl_gio -lrt -lpthread -lcrypto

obj/nc_inst_bytes_tests.o: src/validator/x86/nc_inst_bytes_tests.cc
	g++ ${CXXFLAGS} -o obj/nc_inst_bytes_tests.o ${CXXFLAGS1} -Igtest/include src/validator/x86/nc_inst_bytes_tests.cc

test/x86_validator_tests_nc_inst_bytes: obj/nc_inst_bytes_tests.o obj/libnacl_validate_x86_64.a obj/libnacl_validate_reg_sfi_x86_64.a obj/libnacl_copy_x86_64.a obj/libnacl_decoder_x86_64.a obj/libnacl_opcode_modeling_x86_64.a obj/libnacl_validate_base_x86_64.a obj/libnacl_platform.a obj/libnacl_gio.a
	g++ ${CXXFLAGS} -o test/x86_validator_tests_nc_inst_bytes ${CXXFLAGS2} obj/nc_inst_bytes_tests.o -L/usr/lib -Llib -Lgtest -lgtest -lnacl_validate_base_x86_64 -lnacl_validate_x86_64 -lnacl_validate_reg_sfi_x86_64 -lnacl_copy_x86_64 -lnacl_decoder_x86_64 -lnacl_opcode_modeling_x86_64 -lnacl_platform -lnacl_gio -lrt -lpthread -lcrypto

obj/nc_remaining_memory_tests.o: src/validator/x86/nc_remaining_memory_tests.cc
	g++ ${CXXFLAGS} -o obj/nc_remaining_memory_tests.o ${CXXFLAGS1} -Igtest/include src/validator/x86/nc_remaining_memory_tests.cc

test/x86_validator_tests_nc_remaining_memory: obj/nc_remaining_memory_tests.o obj/libnacl_validate_x86_64.a obj/libnacl_validate_reg_sfi_x86_64.a obj/libnacl_copy_x86_64.a obj/libnacl_decoder_x86_64.a obj/libnacl_opcode_modeling_x86_64.a obj/libnacl_validate_base_x86_64.a obj/libnacl_platform.a obj/libnacl_gio.a
	g++ ${CXXFLAGS} -o test/x86_validator_tests_nc_remaining_memory ${CXXFLAGS2} obj/nc_remaining_memory_tests.o -L/usr/lib -Llib -Lgtest -lgtest -lnacl_validate_base_x86_64 -lnacl_validate_x86_64 -lnacl_validate_reg_sfi_x86_64 -lnacl_copy_x86_64 -lnacl_decoder_x86_64 -lnacl_opcode_modeling_x86_64 -lnacl_platform -lnacl_gio -lrt -lpthread -lcrypto

clean: clean_intermediate
	rm lib/*
	echo libs have been deleted

clean_intermediate:
	rm obj/*
	echo object files have been deleted
	rm test/*
	echo test files have been deleted

obj/libnacl_fault_inject.a: obj/fault_injection.o
	ar rc lib/libnacl_fault_inject.a obj/fault_injection.o

obj/libnacl_platform.a: obj/nacl_exit.o obj/nacl_find_addrsp.o obj/nacl_host_desc.o obj/nacl_host_dir.o obj/nacl_secure_random.o obj/nacl_semaphore.o obj/nacl_thread_id.o obj/nacl_threads.o obj/nacl_time.o obj/nacl_timestamp.o obj/condition_variable.o obj/lock.o obj/nacl_check.o obj/nacl_global_secure_random.o obj/nacl_host_desc_common.o obj/nacl_interruptible_condvar.o obj/nacl_interruptible_mutex.o obj/nacl_log.o obj/nacl_secure_random_common.o obj/nacl_sync_checked.o obj/nacl_time_common.o obj/platform_init.o obj/refcount_base.o
	ar rc lib/libnacl_platform.a obj/nacl_exit.o obj/nacl_find_addrsp.o obj/nacl_host_desc.o obj/nacl_host_dir.o obj/nacl_secure_random.o obj/nacl_semaphore.o obj/nacl_thread_id.o obj/nacl_threads.o obj/nacl_time.o obj/nacl_timestamp.o obj/condition_variable.o obj/lock.o obj/nacl_check.o obj/nacl_global_secure_random.o obj/nacl_host_desc_common.o obj/nacl_interruptible_condvar.o obj/nacl_interruptible_mutex.o obj/nacl_log.o obj/nacl_secure_random_common.o obj/nacl_sync_checked.o obj/nacl_time_common.o obj/platform_init.o obj/refcount_base.o

obj/libnacl_platform_qualify.a: obj/nacl_os_qualify.o obj/sysv_shm_and_mmap.o obj/nacl_dep_qualify.o obj/nacl_cpuwhitelist.o obj/nacl_dep_qualify_arch.o
	ar rc lib/libnacl_platform_qualify.a obj/nacl_os_qualify.o obj/sysv_shm_and_mmap.o obj/nacl_dep_qualify.o obj/nacl_cpuwhitelist.o obj/nacl_dep_qualify_arch.o

obj/libnacl_validate_x86_64.a: obj/ncvalidate.o
	ar rc lib/libnacl_validate_x86_64.a obj/ncvalidate.o

obj/libnacl_validate_reg_sfi_x86_64.a: obj/ncvalidate_iter.o obj/ncvalidate_iter_detailed.o obj/ncvalidator_registry.o obj/ncvalidator_registry_detailed.o obj/nc_cpu_checks.o obj/nc_illegal.o obj/nc_jumps.o obj/address_sets.o obj/nc_jumps_detailed.o obj/nc_opcode_histogram.o obj/nc_protect_base.o obj/nc_memory_protect.o obj/ncvalidate_utils.o obj/ncval_decode_tables.o
	ar rc lib/libnacl_validate_reg_sfi_x86_64.a obj/ncvalidate_iter.o obj/ncvalidate_iter_detailed.o obj/ncvalidator_registry.o obj/ncvalidator_registry_detailed.o obj/nc_cpu_checks.o obj/nc_illegal.o obj/nc_jumps.o obj/address_sets.o obj/nc_jumps_detailed.o obj/nc_opcode_histogram.o obj/nc_protect_base.o obj/nc_memory_protect.o obj/ncvalidate_utils.o obj/ncval_decode_tables.o

obj/libnacl_copy_x86_64.a: obj/nccopycode.o obj/nccopycode_stores.o
	ar rc lib/libnacl_copy_x86_64.a obj/nccopycode.o obj/nccopycode_stores.o

obj/libnacl_decoder_x86_64.a: obj/nc_inst_iter.o obj/nc_inst_state.o obj/nc_inst_trans.o obj/ncop_exps.o
	ar rc lib/libnacl_decoder_x86_64.a obj/nc_inst_iter.o obj/nc_inst_state.o obj/nc_inst_trans.o obj/ncop_exps.o

obj/libnacl_opcode_modeling_x86_64.a: obj/ncopcode_desc.o
	ar rc lib/libnacl_opcode_modeling_x86_64.a obj/ncopcode_desc.o

obj/libnacl_validate_base_x86_64.a: obj/error_reporter.o obj/halt_trim.o obj/nacl_cpuid.o obj/nacl_xgetbv.o obj/ncinstbuffer.o obj/x86_insts.o obj/nc_segment.o
	ar rc lib/libnacl_validate_base_x86_64.a obj/error_reporter.o obj/halt_trim.o obj/nacl_cpuid.o obj/nacl_xgetbv.o obj/ncinstbuffer.o obj/x86_insts.o obj/nc_segment.o

obj/libnacl_gio.a: obj/gio.o obj/gio_mem.o obj/gprintf.o obj/gio_mem_snapshot.o
	ar rc lib/libnacl_gio.a obj/gio.o obj/gio_mem.o obj/gprintf.o obj/gio_mem_snapshot.o


######################################################################## compilation to obj

obj/ncvalidate.o: src/validator/x86/64/ncvalidate.c
	gcc ${CCFLAGS} -o obj/ncvalidate.o ${CCFLAGS0} ${CCFLAGS1} ${CCFLAGS4} src/validator/x86/64/ncvalidate.c

obj/nccopycode_stores.o: src/validator_x86/nccopycode_stores.S
	gcc ${CCFLAGS} -o obj/nccopycode_stores.o ${CCFLAGS0} ${CCFLAGS2} src/validator_x86/nccopycode_stores.S

obj/nacl_xgetbv.o: src/validator/x86/nacl_xgetbv.S
	gcc ${CCFLAGS} -o obj/nacl_xgetbv.o ${CCFLAGS0} ${CCFLAGS2} src/validator/x86/nacl_xgetbv.S


obj/gio_shm.o: src/gio/gio_shm.c
	gcc ${CCFLAGS} -o obj/gio_shm.o ${CCFLAGS0} ${CCFLAGS1} src/gio/gio_shm.c

obj/gio_shm_unbounded.o: src/gio/gio_shm_unbounded.c
	gcc ${CCFLAGS} -o obj/gio_shm_unbounded.o ${CCFLAGS0} ${CCFLAGS1} src/gio/gio_shm_unbounded.c

obj/gio_nacl_desc.o: src/gio/gio_nacl_desc.c
	gcc ${CCFLAGS} -o obj/gio_nacl_desc.o ${CCFLAGS0} ${CCFLAGS1} src/gio/gio_nacl_desc.c

obj/fault_injection.o: src/fault_injection/fault_injection.c
	gcc ${CCFLAGS} -o obj/fault_injection.o ${CCFLAGS0} ${CCFLAGS1} src/fault_injection/fault_injection.c

obj/nacl_os_qualify.o: src/platform_qualify/linux/nacl_os_qualify.c
	gcc ${CCFLAGS} -o obj/nacl_os_qualify.o ${CCFLAGS0} ${CCFLAGS1} src/platform_qualify/linux/nacl_os_qualify.c

obj/sysv_shm_and_mmap.o: src/platform_qualify/linux/sysv_shm_and_mmap.c
	gcc ${CCFLAGS} -o obj/sysv_shm_and_mmap.o ${CCFLAGS0} ${CCFLAGS1} src/platform_qualify/linux/sysv_shm_and_mmap.c

obj/nacl_dep_qualify.o: src/platform_qualify/posix/nacl_dep_qualify.c
	gcc ${CCFLAGS} -o obj/nacl_dep_qualify.o ${CCFLAGS0} ${CCFLAGS1} src/platform_qualify/posix/nacl_dep_qualify.c

obj/nacl_cpuwhitelist.o: src/platform_qualify/arch/x86/nacl_cpuwhitelist.c
	gcc ${CCFLAGS} -o obj/nacl_cpuwhitelist.o ${CCFLAGS0} ${CCFLAGS1} src/platform_qualify/arch/x86/nacl_cpuwhitelist.c

obj/nacl_dep_qualify_arch.o: src/platform_qualify/arch/x86_64/nacl_dep_qualify_arch.c
	gcc ${CCFLAGS} -o obj/nacl_dep_qualify_arch.o ${CCFLAGS0} ${CCFLAGS1} src/platform_qualify/arch/x86_64/nacl_dep_qualify_arch.c

obj/ncvalidate_iter.o: src/validator/x86/ncval_reg_sfi/ncvalidate_iter.c
	gcc ${CCFLAGS} -o obj/ncvalidate_iter.o ${CCFLAGS0} ${CCFLAGS1} src/validator/x86/ncval_reg_sfi/ncvalidate_iter.c

obj/ncvalidate_iter_detailed.o: src/validator/x86/ncval_reg_sfi/ncvalidate_iter_detailed.c
	gcc ${CCFLAGS} -o obj/ncvalidate_iter_detailed.o ${CCFLAGS0} ${CCFLAGS1} src/validator/x86/ncval_reg_sfi/ncvalidate_iter_detailed.c

obj/ncvalidator_registry.o: src/validator/x86/ncval_reg_sfi/ncvalidator_registry.c
	gcc ${CCFLAGS} -o obj/ncvalidator_registry.o ${CCFLAGS0} ${CCFLAGS1} src/validator/x86/ncval_reg_sfi/ncvalidator_registry.c

obj/ncvalidator_registry_detailed.o: src/validator/x86/ncval_reg_sfi/ncvalidator_registry_detailed.c
	gcc ${CCFLAGS} -o obj/ncvalidator_registry_detailed.o ${CCFLAGS0} ${CCFLAGS1} src/validator/x86/ncval_reg_sfi/ncvalidator_registry_detailed.c

obj/nc_cpu_checks.o: src/validator/x86/ncval_reg_sfi/nc_cpu_checks.c
	gcc ${CCFLAGS} -o obj/nc_cpu_checks.o ${CCFLAGS0} ${CCFLAGS1} src/validator/x86/ncval_reg_sfi/nc_cpu_checks.c

obj/nc_illegal.o: src/validator/x86/ncval_reg_sfi/nc_illegal.c
	gcc ${CCFLAGS} -o obj/nc_illegal.o ${CCFLAGS0} ${CCFLAGS1} src/validator/x86/ncval_reg_sfi/nc_illegal.c

obj/nc_jumps.o: src/validator/x86/ncval_reg_sfi/nc_jumps.c
	gcc ${CCFLAGS} -o obj/nc_jumps.o ${CCFLAGS0} ${CCFLAGS1} src/validator/x86/ncval_reg_sfi/nc_jumps.c

obj/address_sets.o: src/validator/x86/ncval_reg_sfi/address_sets.c
	gcc ${CCFLAGS} -o obj/address_sets.o ${CCFLAGS0} ${CCFLAGS1} src/validator/x86/ncval_reg_sfi/address_sets.c

obj/nc_jumps_detailed.o: src/validator/x86/ncval_reg_sfi/nc_jumps_detailed.c
	gcc ${CCFLAGS} -o obj/nc_jumps_detailed.o ${CCFLAGS0} ${CCFLAGS1} src/validator/x86/ncval_reg_sfi/nc_jumps_detailed.c

obj/nc_opcode_histogram.o: src/validator/x86/ncval_reg_sfi/nc_opcode_histogram.c
	gcc ${CCFLAGS} -o obj/nc_opcode_histogram.o ${CCFLAGS0} ${CCFLAGS1} src/validator/x86/ncval_reg_sfi/nc_opcode_histogram.c

obj/nc_protect_base.o: src/validator/x86/ncval_reg_sfi/nc_protect_base.c
	gcc ${CCFLAGS} -o obj/nc_protect_base.o ${CCFLAGS0} ${CCFLAGS1} src/validator/x86/ncval_reg_sfi/nc_protect_base.c

obj/nc_memory_protect.o: src/validator/x86/ncval_reg_sfi/nc_memory_protect.c
	gcc ${CCFLAGS} -o obj/nc_memory_protect.o ${CCFLAGS0} ${CCFLAGS1} src/validator/x86/ncval_reg_sfi/nc_memory_protect.c

obj/ncvalidate_utils.o: src/validator/x86/ncval_reg_sfi/ncvalidate_utils.c
	gcc ${CCFLAGS} -o obj/ncvalidate_utils.o ${CCFLAGS0} ${CCFLAGS1} src/validator/x86/ncval_reg_sfi/ncvalidate_utils.c

obj/ncval_decode_tables.o: src/validator/x86/ncval_reg_sfi/ncval_decode_tables.c
	gcc ${CCFLAGS} -o obj/ncval_decode_tables.o ${CCFLAGS0} ${CCFLAGS1} src/validator/x86/ncval_reg_sfi/ncval_decode_tables.c

obj/nccopycode.o: src/validator_x86/nccopycode.c
	gcc ${CCFLAGS} -o obj/nccopycode.o ${CCFLAGS0} ${CCFLAGS1} src/validator_x86/nccopycode.c

obj/nc_inst_iter.o: src/validator/x86/decoder/nc_inst_iter.c
	gcc ${CCFLAGS} -o obj/nc_inst_iter.o ${CCFLAGS0} ${CCFLAGS1} src/validator/x86/decoder/nc_inst_iter.c

obj/nc_inst_state.o: src/validator/x86/decoder/nc_inst_state.c
	gcc ${CCFLAGS} -o obj/nc_inst_state.o ${CCFLAGS0} ${CCFLAGS1} src/validator/x86/decoder/nc_inst_state.c

obj/nc_inst_trans.o: src/validator/x86/decoder/nc_inst_trans.c
	gcc ${CCFLAGS} -o obj/nc_inst_trans.o ${CCFLAGS0} ${CCFLAGS1} src/validator/x86/decoder/nc_inst_trans.c

obj/ncop_exps.o: src/validator/x86/decoder/ncop_exps.c
	gcc ${CCFLAGS} -o obj/ncop_exps.o ${CCFLAGS0} ${CCFLAGS1} src/validator/x86/decoder/ncop_exps.c

obj/ncopcode_desc.o: src/validator/x86/decoder/ncopcode_desc.c
	gcc ${CCFLAGS} -o obj/ncopcode_desc.o ${CCFLAGS0} ${CCFLAGS1} src/validator/x86/decoder/ncopcode_desc.c

obj/error_reporter.o: src/validator/x86/error_reporter.c
	gcc ${CCFLAGS} -o obj/error_reporter.o ${CCFLAGS0} ${CCFLAGS1} src/validator/x86/error_reporter.c

obj/halt_trim.o: src/validator/x86/halt_trim.c
	gcc ${CCFLAGS} -o obj/halt_trim.o ${CCFLAGS0} ${CCFLAGS1} src/validator/x86/halt_trim.c

obj/nacl_cpuid.o: src/validator/x86/nacl_cpuid.c
	gcc ${CCFLAGS} -o obj/nacl_cpuid.o ${CCFLAGS0} ${CCFLAGS1} src/validator/x86/nacl_cpuid.c

obj/ncinstbuffer.o: src/validator/x86/ncinstbuffer.c
	gcc ${CCFLAGS} -o obj/ncinstbuffer.o ${CCFLAGS0} ${CCFLAGS1} src/validator/x86/ncinstbuffer.c

obj/x86_insts.o: src/validator/x86/x86_insts.c
	gcc ${CCFLAGS} -o obj/x86_insts.o ${CCFLAGS0} ${CCFLAGS1} src/validator/x86/x86_insts.c

obj/nc_segment.o: src/validator/x86/nc_segment.c
	gcc ${CCFLAGS} -o obj/nc_segment.o ${CCFLAGS0} ${CCFLAGS1} src/validator/x86/nc_segment.c

obj/nacl_exit.o: src/platform/linux/nacl_exit.c
	gcc ${CCFLAGS} -o obj/nacl_exit.o ${CCFLAGS0} ${CCFLAGS1} src/platform/linux/nacl_exit.c

obj/nacl_find_addrsp.o: src/platform/linux/nacl_find_addrsp.c
	gcc ${CCFLAGS} -o obj/nacl_find_addrsp.o ${CCFLAGS0} ${CCFLAGS1} src/platform/linux/nacl_find_addrsp.c

obj/nacl_host_desc.o: src/platform/linux/nacl_host_desc.c
	gcc ${CCFLAGS} -o obj/nacl_host_desc.o ${CCFLAGS0} ${CCFLAGS1} src/platform/linux/nacl_host_desc.c

obj/nacl_host_dir.o: src/platform/linux/nacl_host_dir.c
	gcc ${CCFLAGS} -o obj/nacl_host_dir.o ${CCFLAGS0} ${CCFLAGS1} src/platform/linux/nacl_host_dir.c

obj/nacl_secure_random.o: src/platform/linux/nacl_secure_random.c
	gcc ${CCFLAGS} -o obj/nacl_secure_random.o ${CCFLAGS0} ${CCFLAGS1} src/platform/linux/nacl_secure_random.c

obj/nacl_semaphore.o: src/platform/linux/nacl_semaphore.c
	gcc ${CCFLAGS} -o obj/nacl_semaphore.o ${CCFLAGS0} ${CCFLAGS1} src/platform/linux/nacl_semaphore.c

obj/nacl_thread_id.o: src/platform/linux/nacl_thread_id.c
	gcc ${CCFLAGS} -o obj/nacl_thread_id.o ${CCFLAGS0} ${CCFLAGS1} src/platform/linux/nacl_thread_id.c

obj/nacl_threads.o: src/platform/linux/nacl_threads.c
	gcc ${CCFLAGS} -o obj/nacl_threads.o ${CCFLAGS0} ${CCFLAGS1} src/platform/linux/nacl_threads.c

obj/nacl_time.o: src/platform/linux/nacl_time.c
	gcc ${CCFLAGS} -o obj/nacl_time.o ${CCFLAGS0} ${CCFLAGS1} src/platform/linux/nacl_time.c

obj/nacl_timestamp.o: src/platform/linux/nacl_timestamp.c
	gcc ${CCFLAGS} -o obj/nacl_timestamp.o ${CCFLAGS0} ${CCFLAGS1} src/platform/linux/nacl_timestamp.c

obj/condition_variable.o: src/platform/linux/condition_variable.c
	gcc ${CCFLAGS} -o obj/condition_variable.o ${CCFLAGS0} ${CCFLAGS1} src/platform/linux/condition_variable.c

obj/lock.o: src/platform/linux/lock.c
	gcc ${CCFLAGS} -o obj/lock.o ${CCFLAGS0} ${CCFLAGS1} src/platform/linux/lock.c

obj/nacl_check.o: src/platform/nacl_check.c
	gcc ${CCFLAGS} -o obj/nacl_check.o ${CCFLAGS0} ${CCFLAGS1} src/platform/nacl_check.c

obj/nacl_global_secure_random.o: src/platform/nacl_global_secure_random.c
	gcc ${CCFLAGS} -o obj/nacl_global_secure_random.o ${CCFLAGS0} ${CCFLAGS1} src/platform/nacl_global_secure_random.c

obj/nacl_host_desc_common.o: src/platform/nacl_host_desc_common.c
	gcc ${CCFLAGS} -o obj/nacl_host_desc_common.o ${CCFLAGS0} ${CCFLAGS1} src/platform/nacl_host_desc_common.c

obj/nacl_interruptible_condvar.o: src/platform/nacl_interruptible_condvar.c
	gcc ${CCFLAGS} -o obj/nacl_interruptible_condvar.o ${CCFLAGS0} ${CCFLAGS1} src/platform/nacl_interruptible_condvar.c

obj/nacl_interruptible_mutex.o: src/platform/nacl_interruptible_mutex.c
	gcc ${CCFLAGS} -o obj/nacl_interruptible_mutex.o ${CCFLAGS0} ${CCFLAGS1} src/platform/nacl_interruptible_mutex.c

obj/nacl_log.o: src/platform/nacl_log.c
	gcc ${CCFLAGS} -o obj/nacl_log.o ${CCFLAGS0} ${CCFLAGS1} src/platform/nacl_log.c

obj/nacl_secure_random_common.o: src/platform/nacl_secure_random_common.c
	gcc ${CCFLAGS} -o obj/nacl_secure_random_common.o ${CCFLAGS0} ${CCFLAGS1} src/platform/nacl_secure_random_common.c

obj/nacl_sync_checked.o: src/platform/nacl_sync_checked.c
	gcc ${CCFLAGS} -o obj/nacl_sync_checked.o ${CCFLAGS0} ${CCFLAGS1} src/platform/nacl_sync_checked.c

obj/nacl_time_common.o: src/platform/nacl_time_common.c
	gcc ${CCFLAGS} -o obj/nacl_time_common.o ${CCFLAGS0} ${CCFLAGS1} src/platform/nacl_time_common.c

obj/platform_init.o: src/platform/platform_init.c
	gcc ${CCFLAGS} -o obj/platform_init.o ${CCFLAGS0} ${CCFLAGS1} src/platform/platform_init.c

obj/gio.o: src/gio/gio.c
	gcc ${CCFLAGS} -o obj/gio.o ${CCFLAGS0} ${CCFLAGS1} src/gio/gio.c

obj/gio_mem.o: src/gio/gio_mem.c
	gcc ${CCFLAGS} -o obj/gio_mem.o ${CCFLAGS0} ${CCFLAGS1} src/gio/gio_mem.c

obj/gprintf.o: src/gio/gprintf.c
	gcc ${CCFLAGS} -o obj/gprintf.o ${CCFLAGS0} ${CCFLAGS1} src/gio/gprintf.c

obj/gio_mem_snapshot.o: src/gio/gio_mem_snapshot.c
	gcc ${CCFLAGS} -o obj/gio_mem_snapshot.o ${CCFLAGS0} ${CCFLAGS1} src/gio/gio_mem_snapshot.c
	
obj/refcount_base.o: src/platform/refcount_base.cc
	g++ ${CXXFLAGS} -o obj/refcount_base.o ${CXXFLAGS1} ${CCFLAGS2} ${CCFLAGS4} src/platform/refcount_base.cc


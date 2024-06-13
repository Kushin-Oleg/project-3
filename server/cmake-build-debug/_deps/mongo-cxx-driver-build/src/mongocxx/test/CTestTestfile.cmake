# CMake generated Testfile for 
# Source directory: /home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/src/mongocxx/test
# Build directory: /home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-build/src/mongocxx/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(driver "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-build/src/mongocxx/test/test_driver")
set_tests_properties(driver PROPERTIES  ENVIRONMENT "CLIENT_SIDE_ENCRYPTION_TESTS_PATH=/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/data/client_side_encryption;URI_OPTIONS_TESTS_PATH=/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/data/uri-options" _BACKTRACE_TRIPLES "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/src/mongocxx/test/CMakeLists.txt;229;add_test;/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/src/mongocxx/test/CMakeLists.txt;0;")
add_test(logging "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-build/src/mongocxx/test/test_logging")
set_tests_properties(logging PROPERTIES  _BACKTRACE_TRIPLES "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/src/mongocxx/test/CMakeLists.txt;230;add_test;/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/src/mongocxx/test/CMakeLists.txt;0;")
add_test(instance "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-build/src/mongocxx/test/test_instance")
set_tests_properties(instance PROPERTIES  _BACKTRACE_TRIPLES "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/src/mongocxx/test/CMakeLists.txt;231;add_test;/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/src/mongocxx/test/CMakeLists.txt;0;")
add_test(crud_specs "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-build/src/mongocxx/test/test_crud_specs")
set_tests_properties(crud_specs PROPERTIES  ENVIRONMENT "CRUD_LEGACY_TESTS_PATH=/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/data/crud/legacy" _BACKTRACE_TRIPLES "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/src/mongocxx/test/CMakeLists.txt;232;add_test;/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/src/mongocxx/test/CMakeLists.txt;0;")
add_test(gridfs_specs "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-build/src/mongocxx/test/test_gridfs_specs")
set_tests_properties(gridfs_specs PROPERTIES  ENVIRONMENT "GRIDFS_TESTS_PATH=/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/data/gridfs" _BACKTRACE_TRIPLES "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/src/mongocxx/test/CMakeLists.txt;233;add_test;/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/src/mongocxx/test/CMakeLists.txt;0;")
add_test(client_side_encryption_specs "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-build/src/mongocxx/test/test_client_side_encryption_specs")
set_tests_properties(client_side_encryption_specs PROPERTIES  ENVIRONMENT "CLIENT_SIDE_ENCRYPTION_LEGACY_TESTS_PATH=/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/data/client_side_encryption/legacy" _BACKTRACE_TRIPLES "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/src/mongocxx/test/CMakeLists.txt;234;add_test;/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/src/mongocxx/test/CMakeLists.txt;0;")
add_test(command_monitoring_specs "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-build/src/mongocxx/test/test_command_monitoring_specs")
set_tests_properties(command_monitoring_specs PROPERTIES  ENVIRONMENT "COMMAND_MONITORING_TESTS_PATH=/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/data/command-monitoring" _BACKTRACE_TRIPLES "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/src/mongocxx/test/CMakeLists.txt;235;add_test;/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/src/mongocxx/test/CMakeLists.txt;0;")
add_test(transactions_specs "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-build/src/mongocxx/test/test_transactions_specs")
set_tests_properties(transactions_specs PROPERTIES  ENVIRONMENT "TRANSACTIONS_LEGACY_TESTS_PATH=/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/data/transactions/legacy;WITH_TRANSACTION_TESTS_PATH=/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/data/with_transaction" _BACKTRACE_TRIPLES "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/src/mongocxx/test/CMakeLists.txt;236;add_test;/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/src/mongocxx/test/CMakeLists.txt;0;")
add_test(retryable_reads_spec "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-build/src/mongocxx/test/test_retryable_reads_specs")
set_tests_properties(retryable_reads_spec PROPERTIES  ENVIRONMENT "RETRYABLE_READS_LEGACY_TESTS_PATH=/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/data/retryable-reads/legacy" _BACKTRACE_TRIPLES "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/src/mongocxx/test/CMakeLists.txt;237;add_test;/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/src/mongocxx/test/CMakeLists.txt;0;")
add_test(read_write_concern_specs "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-build/src/mongocxx/test/test_read_write_concern_specs")
set_tests_properties(read_write_concern_specs PROPERTIES  ENVIRONMENT "READ_WRITE_CONCERN_OPERATION_TESTS_PATH=/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/data/read-write-concern/operation" _BACKTRACE_TRIPLES "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/src/mongocxx/test/CMakeLists.txt;238;add_test;/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/src/mongocxx/test/CMakeLists.txt;0;")
add_test(unified_format_spec "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-build/src/mongocxx/test/test_unified_format_spec")
set_tests_properties(unified_format_spec PROPERTIES  ENVIRONMENT "CHANGE_STREAMS_UNIFIED_TESTS_PATH=/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/data/change-streams/unified;CLIENT_SIDE_ENCRYPTION_UNIFIED_TESTS_PATH=/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/data/client_side_encryption/unified;COLLECTION_MANAGEMENT_TESTS_PATH=/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/data/collection-management;CRUD_UNIFIED_TESTS_PATH=/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/data/crud/unified;INDEX_MANAGEMENT_TESTS_PATH=/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/data/index-management;RETRYABLE_READS_UNIFIED_TESTS_PATH=/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/data/retryable-reads/unified/;RETRYABLE_WRITES_UNIFIED_TESTS_PATH=/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/data/retryable-writes/unified/;SESSION_UNIFIED_TESTS_PATH=/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/data/sessions/unified/;TRANSACTIONS_UNIFIED_TESTS_PATH=/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/data/transactions/unified;UNIFIED_FORMAT_TESTS_PATH=/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/data/unified-format;VERSIONED_API_TESTS_PATH=/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/data/versioned-api" _BACKTRACE_TRIPLES "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/src/mongocxx/test/CMakeLists.txt;239;add_test;/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/src/mongocxx/test/CMakeLists.txt;0;")
add_test(versioned_api "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-build/src/mongocxx/test/test_versioned_api")
set_tests_properties(versioned_api PROPERTIES  _BACKTRACE_TRIPLES "/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/src/mongocxx/test/CMakeLists.txt;240;add_test;/home/kukushka/Рабочий стол/project-3/server/cmake-build-debug/_deps/mongo-cxx-driver-src/src/mongocxx/test/CMakeLists.txt;0;")
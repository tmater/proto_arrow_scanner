project(ProtoArrowScanner)
cmake_minimum_required(VERSION 3.22)

find_package(Arrow REQUIRED)
find_package(Parquet REQUIRED)

add_library(scanners STATIC
  parquet_scanner.h
  parquet_scanner.cpp
  parquet_writer.h
  parquet_writer.cpp)

target_link_libraries(scanners PRIVATE Arrow::arrow_shared)
target_link_libraries(scanners PRIVATE Parquet::parquet_shared)

add_executable(proto_arrow_scanner proto_arrow_scanner_main.cpp)

target_link_libraries(proto_arrow_scanner PRIVATE scanners)
target_link_libraries(proto_arrow_scanner PRIVATE Arrow::arrow_shared)


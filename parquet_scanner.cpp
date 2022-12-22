#include "parquet_scanner.h"

using namespace std;

ParquetScanner::ParquetScanner() {}

int ParquetScanner::Open(string file_name) {
  arrow::Status status = OpenInputStream(file_name);
}

arrow::Status ParquetScanner::OpenInputStream(string file_path) {
  ARROW_ASSIGN_OR_RAISE(infile_, arrow::io::ReadableFile::Open(file_path));
  return arrow::Status::OK();
}

std::shared_ptr<arrow::Table> ParquetScanner::Next() {
  std::unique_ptr<parquet::arrow::FileReader> reader;
  arrow::Status status = parquet::arrow::OpenFile(infile_, arrow::default_memory_pool(),
      &reader);
  std::shared_ptr<arrow::Table> parquet_table;
  status = reader->ReadTable(&parquet_table);
  return parquet_table;
}

int ParquetScanner::Close() {
  // parquet reader does not need to be closed
}

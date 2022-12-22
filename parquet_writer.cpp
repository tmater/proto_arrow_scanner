#include "parquet_writer.h"

using namespace std;

ParquetWriter::ParquetWriter() {}

int ParquetWriter::Open(string file_name) {
  arrow::Status status = OpenOutputStream(file_name);
}

arrow::Status ParquetWriter::OpenOutputStream(string file_path) {
  ARROW_ASSIGN_OR_RAISE(outfile_, arrow::io::FileOutputStream::Open(file_path));
  return arrow::Status::OK();
}

int ParquetWriter::Next(std::shared_ptr<arrow::Table> table) {
  arrow::Status status = parquet::arrow::WriteTable(*table, arrow::default_memory_pool(),
      outfile_, 5);
}

int ParquetWriter::Close() {
  // parquet writer does not need to be closed
}
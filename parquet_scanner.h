#include <arrow/api.h>
#include <arrow/io/api.h>
#include <parquet/arrow/reader.h>

#include <iostream>

class ParquetScanner {
public:
  ParquetScanner();

  int Open(std::string);

  std::shared_ptr<arrow::Table> Next();

  int Close();

private:
  std::shared_ptr<arrow::io::ReadableFile> infile_ = nullptr;

  arrow::Status OpenInputStream(std::string);

};
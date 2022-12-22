#include <arrow/api.h>
#include <arrow/io/api.h>
#include <parquet/arrow/writer.h>

#include <iostream>

class ParquetWriter {
public:

  ParquetWriter();

  int Open(std::string);

  int Next(std::shared_ptr<arrow::Table> table);

  int Close();

private:

  std::shared_ptr<arrow::io::FileOutputStream> outfile_;

  arrow::Status OpenOutputStream(std::string);

};
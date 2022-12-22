#include <arrow/api.h>

#include "parquet_writer.h"
#include "parquet_scanner.h"

#include <iostream>

using namespace std;

arrow::Status CreateTestTable() {
  arrow::Int8Builder int8builder;
  int8_t days_raw2[5] = {6, 12, 3, 30, 22};
  ARROW_RETURN_NOT_OK(int8builder.AppendValues(days_raw2, 5));
  std::shared_ptr<arrow::Array> days2;
  ARROW_ASSIGN_OR_RAISE(days2, int8builder.Finish());
  int8_t months_raw2[5] = {5, 4, 11, 3, 2};
  ARROW_RETURN_NOT_OK(int8builder.AppendValues(months_raw2, 5));
  std::shared_ptr<arrow::Array> months2;
  ARROW_ASSIGN_OR_RAISE(months2, int8builder.Finish());
  arrow::Int16Builder int16builder;
  int16_t years_raw2[5] = {1980, 2001, 1915, 2020, 1996};
  ARROW_RETURN_NOT_OK(int16builder.AppendValues(years_raw2, 5));
  std::shared_ptr<arrow::Array> years2;
  ARROW_ASSIGN_OR_RAISE(years2, int16builder.Finish());
  arrow::ArrayVector day_vecs{days2};
  std::shared_ptr<arrow::ChunkedArray> day_chunks =
      std::make_shared<arrow::ChunkedArray>(day_vecs);
  arrow::ArrayVector month_vecs{months2};
  std::shared_ptr<arrow::ChunkedArray> month_chunks =
      std::make_shared<arrow::ChunkedArray>(month_vecs);
  arrow::ArrayVector year_vecs{years2};
  std::shared_ptr<arrow::ChunkedArray> year_chunks =
      std::make_shared<arrow::ChunkedArray>(year_vecs);

  std::shared_ptr<arrow::Field> field_day, field_month, field_year;
  std::shared_ptr<arrow::Schema> schema;
  field_day = arrow::field("Day", arrow::int8());
  field_month = arrow::field("Month", arrow::int8());
  field_year = arrow::field("Year", arrow::int16());
  schema = arrow::schema({field_day, field_month, field_year});

  std::shared_ptr<arrow::Table> table = arrow::Table::Make(schema, {day_chunks, month_chunks, year_chunks}, 5);

  ParquetWriter* writer = new ParquetWriter();
  writer->Open("test1.parquet");
  writer->Next(table);
  writer->Close();
  return arrow::Status::OK();
}


int main() {

  arrow::Status st = CreateTestTable();
  ParquetScanner* scanner = new ParquetScanner();
  scanner->Open("test1.parquet");
  std::shared_ptr<arrow::Table> table = scanner->Next();
  scanner->Close();

  cout << table->ToString();

  if (!st.ok()) {
    std::cerr << st << std::endl;
    return 1;
  }
  return 0;
}
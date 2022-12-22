

# Build

## Pre-requisites
brew install apache-arrow

## Build steps
```
mkdir -p cmake/build
cd cmake/build
cmake ../..
make -j
```

## Run
```
./cmake/build/proto_arrow_scanner
```

## TODO
ParquetWriter->Write();


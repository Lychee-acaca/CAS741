# RwaveDetection

[![CI](https://github.com/Lychee-acaca/CAS741/actions/workflows/ci.yml/badge.svg)](https://github.com/Lychee-acaca/CAS741/actions/workflows/ci.yml)
[![Codecov](https://codecov.io/gh/Lychee-acaca/CAS741/branch/main/graph/badge.svg)](https://app.codecov.io/gh/Lychee-acaca/CAS741)
![License](https://img.shields.io/badge/License-MIT-blue.svg)

RwaveDetection is a tool for ECG signal processing and R-wave detection.

---

## Build Instructions

### Prerequisites

- C++17 compiler (GCC or Clang)
- [CMake](https://cmake.org/) >= 3.15
- [Ninja](https://ninja-build.org/) (for faster builds)

### Docker

This project provides a Docker image, allowing you to build and test within a
container environment. The build process is the same as described in the Build
(Linux) section below. You can use the following command to pull the image and create a container:

```bash
docker pull lycheeacaca/rwave-dev:latest
git clone https://github.com/Lychee-acaca/CAS741.git
docker run --rm -it --name rwave -v ./CAS741:/workspace/rwave lycheeacaca/rwave-dev:latest /bin/bash
```

### Build (Linux)

```bash
git clone https://github.com/Lychee-acaca/CAS741.git
cd CAS741
./build.sh Release
```

The compiled binary files will appear in `CAS741/build/bin/Release`.

## Usage

You need to prepare a single-channel ECG signal stored in a text file format,
such as `input_signal.txt`. The first line should contain the sampling
frequency, and each subsequent line should contain a sample value of the signal.
Here we use patient 100 from the
[MIT-BIH](https://physionet.org/content/mitdb/1.0.0/) database as an example:

```
input_signal.txt
360
-0.145000
-0.145000
-0.145000
-0.145000
-0.145000
......
-0.075000
-0.445000
-0.675000
-0.765000
-1.280000
```

```bash
./build/bin/Release/RwaveDetection -i ./input_signal.txt -o ./output_signal.txt
```

Then you will see that a file named output_signal.txt has been generated in the
current directory. Each line in this file contains an index, starting from $0$,
indicating that the corresponding index represents an R-wave.

### (Optional) Compare with annotated data

Assuming you have a set of annotated data `ann_data.txt` with the same format as the output of
`output_signal.txt`, you can use the `-a` option to specify it as the reference
annotation. The program will then compare it with the algorithm's output to
calculate the RMSE (Root Mean Square Error).

```bash
./build/bin/Release/RwaveDetection -i ./input_signal.txt -o ./output_signal.txt -a ./ann_data.txt
```

Next, you will see the following information printed to the standard output:

```
xx:xx:xx [LOW] RMSE = 0.771475
```

Under the `test/unitTest/data` directory of the project, you will find
`mitbih_100.txt` and `mitbih_100.ann.txt`. You can use these two files to test
the functionality described above. You should obtain the same RMSE as mentioned above.

```bash
./build/bin/Release/RwaveDetection -i ./test/unitTest/data/mitbih_100.txt -o ./output_signal.txt -a ./test/unitTest/data/mitbih_100.ann.txt
```

---

Developer Names: Junwei Lin

Date of project start: January 16, 2025

This project is a tool for ECG signal processing and R-wave detection.

The folders and files for this project are as follows:

docs - Documentation for the project
refs - Reference material used for the project, including papers
src - Source code
test - Test cases
etc.

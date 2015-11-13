# PA193-Project [![Build status](https://travis-ci.org/Afforix/PA193-Project.svg)](https://travis-ci.org/Afforix/PA193-Project) [![Coverity status](https://scan.coverity.com/projects/6953/badge.svg)](https://scan.coverity.com/projects/afforix-pa193-project)
## Parser of Docker image configuration stored in JSON
Specification defined at https://github.com/docker/docker/blob/master/image/spec/v1.md

__Disclaimer:__ The specification is not particularly strict and in real world configs may appear cases not explicitely mentioned there, for example missing fields. We developed our tool with the specification AND real world examples in mind, however by the nature of the benevolent specification we can never be sure whether our validation is complete.

This project is an assignment for the course Secure coding principles and practices at FI MU (www.fi.muni.cz).
## Dependencies
None, only C++11 capable compiler is required, for example GCC of version at least 4.9. Please use command `make test` to check you development setup.
## Usage
```
make
make test
./parser <input_file>
```
If input is valid image configuration, it is printed, otherwise error is reported to the user. Is capable of validation of individual image config or of an array of image configs, such format uses command `docker inspect IMAGE`, for example `docker inspect base/arch`.

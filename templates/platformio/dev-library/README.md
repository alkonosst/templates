# Template for development of embedded/native libraries

This template is intended for development of embedded (Arduino) and _sometimes_ native-compatible
libraries using PlatformIO.

## Layout

- `examples/` - one folder per example; `*.ino` folders build as Arduino examples, the rest as
  native.
- `scripts/` - build helpers (see below).
- `src/` - the library sources (`MyLib.h`, `MyLib.cpp`).
- `test/` - Unity unit tests run on the native platform.
- `.clang-format` - formatting rules (version 17.0.6, matching the CI gate).
- `CMakeLists-header-only.txt` / `CMakeLists-with-sources.txt` - pick one (see CMake section).
- `library.json` / `library.properties` - PlatformIO and Arduino Library Manager manifests.
- `platformio.ini` - environments for examples, tests, sanitizers and coverage.

## .github

### Workflows

Copy and customize (if needed) the following workflows from
[templates/github/workflows](https://github.com/alkonosst/templates/tree/main/templates/github/workflows):

- [create-release.yml](https://github.com/alkonosst/templates/blob/main/templates/github/workflows/create-release.yml):
  creates a GitHub release and publishes the library to PlatformIO and Arduino Library Manager.
- [pio-ci.yml](https://github.com/alkonosst/templates/blob/main/templates/github/workflows/pio-ci.yml):
  runs the tests, examples and coverage on GitHub Actions.
- [pr-label.yml](https://github.com/alkonosst/templates/blob/main/templates/github/workflows/pr-label.yml):
  adds labels to PRs based on the title based on Conventional Commits.

> [!IMPORTANT]
> Create the following secrets in the GitHub repository for the release workflow to work:
>
> - `CODECOV_TOKEN`: Codecov token for coverage upload.
> - `PLATFORMIO_AUTH_TOKEN`: PlatformIO token for publishing the library (`pio account token`).

### Issue/PR templates

Copy and customize the following issue templates from
[templates/github/ISSUE_TEMPLATE](https://github.com/alkonosst/templates/tree/main/templates/github/ISSUE_TEMPLATE):

- [bug_report.md](https://github.com/alkonosst/templates/blob/main/templates/github/ISSUE_TEMPLATE/bug_report.md):
  template for bug reports.
- [feature_request.md](https://github.com/alkonosst/templates/blob/main/templates/github/ISSUE_TEMPLATE/feature_request.md):
  template for feature requests.
- [config.yml](https://github.com/alkonosst/templates/blob/main/templates/github/ISSUE_TEMPLATE/config.yml):
  configuration for issue/PR templates.

> [!IMPORTANT]
> In `config.yml`, replace `<repository>` with the repository name before using.

Copy and customize the
[PULL_REQUEST_TEMPLATE.md](https://github.com/alkonosst/templates/blob/main/templates/github/PULL_REQUEST_TEMPLATE.md).

### Health files

Copy and customize the following health files from
[templates/github/](https://github.com/alkonosst/templates/tree/main/templates/github/):

- [CODE_OF_CONDUCT.md](https://github.com/alkonosst/templates/blob/main/templates/github/CODE_OF_CONDUCT.md)
- [CONTRIBUTING.md](https://github.com/alkonosst/templates/blob/main/templates/github/CONTRIBUTING.md)
- [FUNDING.yml](https://github.com/alkonosst/templates/blob/main/templates/github/FUNDING.yml)

### Release notes

Copy the
[release.yml](https://github.com/alkonosst/templates/blob/main/templates/github/release.yml)
configuration file.

## Repo settings

- Enable Discussions.
- Enable Sponsorships.

## Customize first

Replace `MyLib` (file names, target names, manifests), the author, the URLs and the description in
`library.json` and `library.properties`. Keep the `version` field in both manifests in sync.

## Environments

These are default environments in `platformio.ini`. If needed, it can be extended with more
environments for other boards, examples or tests.

| Environment        | Command                       | Purpose                                |
| ------------------ | ----------------------------- | -------------------------------------- |
| `native-test`      | `pio test -e native-test`     | Fast native unit tests.                |
| `native-san-test`  | `pio test -e native-san-test` | Native tests with ASan + UBSan.        |
| `native-cov-test`  | `pio test -e native-cov-test` | Native tests built with gcov coverage. |
| `esp32-s3-test`    | `pio test -e esp32-s3-test`   | Unit tests on real ESP32-S3 hardware.  |
| `native-example`   | see below                     | Compile/run one example natively.      |
| `esp32-s3-example` | see below                     | Compile/flash one example on ESP32-S3. |

### Running an example

The example to build is selected with the `EXAMPLE` environment variable (a path relative to the
project root). `scripts/require-example.py` aborts the build with a clear message if it is unset or
points to a missing folder.

```sh
# Native (Linux/WSL)
export EXAMPLE="examples/native-example"; pio run -e native-example -t exec

# Native (PowerShell)
$env:EXAMPLE="examples/native-example"; pio run -e native-example -t exec

# ESP32-S3
export EXAMPLE="examples/arduino-example"; pio run -e esp32-s3-example -t upload -t monitor
```

### Coverage

`scripts/coverage.py` creates a custom target that runs the tests and generates a coverage report to
`coverage/`. Usage:

```sh
pio run -e native-cov-test -t coverage
```

## CMake (for FetchContent consumers)

Pick the variant that matches the library and rename it to `CMakeLists.txt`:

- `CMakeLists-header-only.txt` - header-only library (`INTERFACE` target).
- `CMakeLists-with-sources.txt` - library with `.cpp` sources (`STATIC` target).

Both expose the target as `alkonosst::MyLib`.

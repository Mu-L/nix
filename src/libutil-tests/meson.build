project('nix-util-tests', 'cpp',
  version : files('.version'),
  default_options : [
    'cpp_std=c++2a',
    # TODO(Qyriad): increase the warning level
    'warning_level=1',
    'errorlogs=true', # Please print logs for tests that fail
  ],
  meson_version : '>= 1.1',
  license : 'LGPL-2.1-or-later',
)

cxx = meson.get_compiler('cpp')

subdir('nix-meson-build-support/deps-lists')

deps_private_maybe_subproject = [
  dependency('nix-util'),
  dependency('nix-util-c'),
  dependency('nix-util-test-support'),
]
deps_public_maybe_subproject = [
]
subdir('nix-meson-build-support/subprojects')

subdir('nix-meson-build-support/export-all-symbols')
subdir('nix-meson-build-support/windows-version')

rapidcheck = dependency('rapidcheck')
deps_private += rapidcheck

gtest = dependency('gtest', main : true)
deps_private += gtest

configdata = configuration_data()
configdata.set_quoted('PACKAGE_VERSION', meson.project_version())

config_priv_h = configure_file(
  configuration : configdata,
  output : 'util-tests-config.hh',
)

subdir('nix-meson-build-support/common')

sources = files(
  'args.cc',
  'canon-path.cc',
  'checked-arithmetic.cc',
  'chunked-vector.cc',
  'closure.cc',
  'compression.cc',
  'config.cc',
  'executable-path.cc',
  'file-content-address.cc',
  'file-system.cc',
  'git.cc',
  'hash.cc',
  'hilite.cc',
  'json-utils.cc',
  'logging.cc',
  'lru-cache.cc',
  'monitorfdhup.cc',
  'nix_api_util.cc',
  'pool.cc',
  'position.cc',
  'processes.cc',
  'references.cc',
  'sort.cc',
  'spawn.cc',
  'strings.cc',
  'suggestions.cc',
  'terminal.cc',
  'url.cc',
  'util.cc',
  'xml-writer.cc',
)

include_dirs = [include_directories('.')]


this_exe = executable(
  meson.project_name(),
  sources,
  config_priv_h,
  dependencies : deps_private_subproject + deps_private + deps_other,
  include_directories : include_dirs,
  # TODO: -lrapidcheck, see ../libutil-support/build.meson
  link_args: linker_export_flags + ['-lrapidcheck'],
  # get main from gtest
  install : true,
)

test(
  meson.project_name(),
  this_exe,
  env : {
    '_NIX_TEST_UNIT_DATA': meson.current_source_dir() / 'data',
  },
  protocol : 'gtest',
)

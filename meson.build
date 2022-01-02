project('zombie', 'c')

add_project_arguments('-D_POSIX_C_SOURCE=200809L', language: 'c')

cc = meson.get_compiler('c')
librt = cc.find_library('rt')

test('test_zombie0', executable('zombie0',
				['src/memory.c', 'src/test.c', 'src/zombie0.c'],
				include_directories: 'include/',
				dependencies: librt))

test('test_zombie1', executable('zombie1',
				['src/memory.c', 'src/test.c', 'src/zombie1.c'],
				include_directories: 'include/',
				dependencies: librt))

test('test_zombie2', executable('zombie2',
				['src/memory.c', 'src/test.c', 'src/zombie2.c'],
				include_directories: 'include/',
				dependencies: librt))

test('test_zombie3', executable('zombie3',
				['src/memory.c', 'src/test.c', 'src/zombie3.c'],
				include_directories: 'include/',
				dependencies: librt))

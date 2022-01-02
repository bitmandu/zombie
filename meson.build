project('zombie', 'c')

add_project_arguments('-D_POSIX_C_SOURCE=200809L', language: 'c')

test('test_zombie1', executable('zombie1',
				['src/memory.c', 'src/zombie1.c'],
				include_directories: 'include/'))

test('test_zombie2', executable('zombie2',
				['src/memory.c', 'src/zombie2.c'],
				include_directories: 'include/'))

test('test_zombie3', executable('zombie3',
				['src/memory.c', 'src/zombie3.c'],
				include_directories: 'include/'))

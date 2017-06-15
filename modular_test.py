import subprocess
import sys

class module_test:
    def __init__(self, module_char, input_file, output_file, expected_file):
        self.m = module_char
        self.i = input_file
        self.o = output_file
        self.e = expected_file

subprocess.call('make',shell=True)

spur_test = module_test('S',
                        'test_files/spur_input.txt',
                        'spur_output.txt',
                        'test_files/spur_expected.txt')

rack_test = module_test('R',
                        'test_files/rack_input.txt',
                        'rack_output.txt',
                        'test_files/rack_expected.txt')

metric_test = module_test('U',
                          'test_files/metric_input.txt',
                          'metric_output.txt',
                          'test_files/metric_expected.txt')

spur_wrong_format = module_test('S',
                                'test_files/spur_wrong_format.txt',
                                'spur_output.txt',
                                'test_files/wrong_expected.txt')

spur_wrong_vals = module_test('S',
                              'test_files/spur_wrong_vals.txt',
                              'spur_output.txt',
                              'test_files/wrong_expected.txt')

rack_wrong_format = module_test('R',
                                'test_files/rack_wrong_format.txt',
                                'rack_output.txt',
                                'test_files/wrong_expected.txt')

rack_wrong_vals = module_test('R',
                              'test_files/rack_wrong_vals.txt',
                              'rack_output.txt',
                              'test_files/wrong_expected.txt')

metric_wrong_format = module_test('U',
                                  'test_files/metric_wrong_format.txt',
                                  'metric_output.txt',
                                  'test_files/wrong_expected.txt')

metric_wrong_vals = module_test('U',
                                'test_files/metric_wrong_vals.txt',
                                'metric_output.txt',
                                'test_files/wrong_expected.txt')

tests=[spur_test,rack_test,metric_test] # correct functioning
tests += [spur_wrong_format,
          spur_wrong_vals,
          rack_wrong_format,
          rack_wrong_vals,
          metric_wrong_format,
          metric_wrong_vals] # stress test

for i in range(0,len(tests)):
    bash_test=' '.join(['bash -x system_test.sh',
                        tests[i].m,
                        tests[i].i,
                        tests[i].o,
                        tests[i].e,
                        '> test_'+str(i)+'.txt'])
    subprocess.call(bash_test,shell=True)
    if 'Test failed' in open('test_'+str(i)+'.txt').read():
        sys.exit()
    print('rm test_'+str(i)+'.txt')
    subprocess.call('rm test_'+str(i)+'.txt',shell=True)

subprocess.call('make clean',shell=True)

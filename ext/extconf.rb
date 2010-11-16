# Loads mkmf which is used to make makefiles for Ruby extensions
require 'rubygems'
require 'mkmf'

$CPPFLAGS << "-fno-stack-protector -I../SPIKE/SPIKE/include"
dir_config(ENV['PWD'])
have_library("dlrpc", "new_spike")
have_library('dl')
create_makefile('rspike')

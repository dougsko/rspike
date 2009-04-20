#!/usr/bin/env ruby
#
#
# ruby version of line_send_tcp.c
#

require 'ext/rspike'

# usage: ./line_send_tcp 192.168.1.100 701 something.spk 0 0
#

host = ARGV[0]
port = ARGV[1].to_i
script = ARGV[2]

skipvars = ARGV[3]
skipfuzzstr = ARGV[4]

s = Spike.new
s.set_spike
s.init_fuzz

s.reset_fuzzstr

fuzzvarnum = 0
fuzzstrnum = 0
firstfuzz = 1

puts "Fuzzing"
while(! s.didlastvar?) do
	s.reset_fuzzstr

	if(firstfuzz == 1)
		if (fuzzvarnum.to_i < skipvars.to_i )
			for i in 0..skipvars do
				s.inc_fuzzvar
			end
		end
		if (fuzzstrnum.to_i < skipfuzzstr.to_i)
			for i in 0..skipvars do
				s.inc_fuzzstr
			end
		end
		firstfuzz = 0
	else
		fuzzstrnum = 0
	end

	while(! s.didlastfuzzstr?) do
		s.clear
		puts "Fuzzing Variable #{fuzzvarnum}:#{fuzzstrnum}"

		s.connect_tcp(host, port)
		s.readline
		puts "Read first line"
		s.parse(script)

		if (! s.send_lines)
			puts "Couldn't send data!"
			s.close_tcp
		end

		s.close_tcp
		fuzzstrnum += 1
		s.inc_fuzzstr
	end

	fuzzvarnum += 1
	s.inc_fuzzvar
end

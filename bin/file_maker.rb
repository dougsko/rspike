#!/usr/bin/env ruby
#
#
# make fuzzed up files
#

require 'rubygems'
require 'rspike'

if ARGV.size < 3 or ARGV[0] =~ /-h|--help/
    puts "\nExample usage: #{__FILE__} data/spike_files/pls.spk 0 0\n"
    exit
end

script = ARGV[0]

skipvars = ARGV[1]
skipfuzzstr = ARGV[2]

s = RSpike.new
s.set_spike
s.init_fuzz

s.reset_fuzzstr

fuzzvarnum = 0
fuzzstrnum = 0
firstfuzz = 1

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
		s.parse(script)

        File.open("data/foo#{fuzzvarnum}#{fuzzstrnum}.pls", "w") do |f|
            f.puts s.get_databuf
        end    

		fuzzstrnum += 1
		s.inc_fuzzstr
	end

	fuzzvarnum += 1
	s.inc_fuzzvar
end

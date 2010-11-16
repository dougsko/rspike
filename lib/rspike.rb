#!/usr/bin/env ruby
#
#

require 'rspike.so'

class SpikeObject
    attr_accessor :fuzzvarnum, :fuzzstrnum, :string
    def initialize(fuzzvarnum, fuzzstrnum, string)
        @fuzzvarnum = fuzzvarnum.to_s
        @fuzzstrnum = fuzzstrnum.to_s
        @string = string
    end
end

class RSpike
    def generate(script)
        self.set_spike
        self.init_fuzz

        self.reset_fuzzstr

        fuzzvarnum = 0
        fuzzstrnum = 0

        while(! self.didlastvar?) do
            self.reset_fuzzstr
            while(! self.didlastfuzzstr?) do
                self.clear
                self.parse(script)
                so = SpikeObject.new(fuzzvarnum, fuzzstrnum, self.get_databuf)
                yield so

                fuzzstrnum += 1
                self.inc_fuzzstr
            end
            fuzzvarnum += 1
            self.inc_fuzzvar
        end
    end
end

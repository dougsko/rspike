#!/usr/bin/env ruby
#
#

require 'rspike.so'

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
                yield self.get_databuf

                fuzzstrnum += 1
                self.inc_fuzzstr
            end
            fuzzvarnum += 1
            self.inc_fuzzvar
        end
    end
end

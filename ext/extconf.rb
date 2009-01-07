require 'mkmf'

spikesrc = ENV["PWD"] + "/ext/SPIKE/SPIKE/src"
#spikesrc = "SPIKE/SPIKE/src"
ENV['LD_LIBRARY_PATH'] = spikesrc

$CC = "gcc-3.4"
# $LOCAL_LIBS = "-ldlrpc"
$CFLAGS = "-Wall -I./SPIKE/SPIKE/include -I#{spikesrc}"

srcs = ["rspike.c", "#{spikesrc}/spike.c", "#{spikesrc}/hdebug.c", 
	"#{spikesrc}/tcpstuff.c", "#{spikesrc}/udpstuff.c", "#{spikesrc}/dlrpc.c", "-L#{spikesrc}"]

find_library("dlrpc", "new_spike", "#{spikesrc}")

$objs = srcs.collect { |f| f.sub(".c", ".o") }

create_makefile("rspike")



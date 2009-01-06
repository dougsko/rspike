#include "ruby.h"
#include "spike.h"

static VALUE rb_cSpike;

static void rspike_mark(struct spike *s){
}

static void rspike_free(struct spike *s){
	spike_free(s);
}

static VALUE rspike_allocate(VALUE klass){
	struct spike *s;
	
	s = new_spike();
	return Data_Wrap_Struct(klass, rspike_mark, rspike_free, s);
}

static VALUE rb_set_spike(VALUE self){
	struct spike *s;

	Data_Get_Struct(self, struct spike, s);
	return INT2NUM(setspike(s));
}

static VALUE rb_init_fuzzing(VALUE self){
	s_init_fuzzing();
	return Qnil;
}

static VALUE rb_didlastvariable(VALUE self){
	int ret;
	
	if((ret = s_didlastvariable()))
		return INT2NUM(ret);
	else
		return Qnil;
}

static VALUE rb_reset_fuzzstring(VALUE self){
	s_resetfuzzstring();
	return Qnil;
}

static VALUE rb_increment_fuzzvar(VALUE self){
	s_incrementfuzzvariable();
	return Qnil;
}

static VALUE rb_increment_fuzzstring(VALUE self){
	s_incrementfuzzstring();
	return Qnil;
}

static VALUE rb_didlastfuzzstring(VALUE self){
	int ret;

	if((ret = s_didlastfuzzstring()))
		return INT2NUM(ret);
	else
		return Qnil;
}

static VALUE rb_spikeclear(VALUE self){
	return INT2NUM(spike_clear());
}

static VALUE rb_connect_tcp(VALUE self, VALUE rb_host, VALUE rb_port){
	char *host;
	int port;

	host = STR2CSTR(rb_host);
	port = NUM2INT(rb_port);
	return INT2NUM(spike_connect_tcp(host,port));
}

static VALUE rb_readline(VALUE self){
	return INT2NUM(s_readline());
}

static VALUE rb_parse(VALUE self, VALUE rb_script){
	char *script;

	script = STR2CSTR(rb_script);
	return INT2NUM(s_parse(script));
}

static VALUE rb_close_tcp(VALUE self){
	spike_close_tcp();
	return Qnil;
}

static VALUE rb_send_lines(VALUE self){
	int ret;
	
	if((ret = s_send_lines()) < 0)
		 return Qnil;
	else
		return INT2NUM(ret);
}

static VALUE rb_string(VALUE self, VALUE string){
	char *instring;

	instring = STR2CSTR(string);
	return INT2NUM(s_string(instring));
}

static VALUE rb_blocksize_string(VALUE self, VALUE string, VALUE len){
	char *instring;
	int size;

	instring = STR2CSTR(string);
	size = NUM2INT(len);

	return INT2NUM(s_blocksize_string(instring, size));
}

static VALUE rb_binary(VALUE self, VALUE string){
	char *instring;

	instring = STR2CSTR(string);
	return INT2NUM(s_binary(instring));
}

static VALUE rb_push(VALUE self, VALUE topush, VALUE len){
	char *pushme;
	unsigned long size;

	pushme = STR2CSTR(topush);
	size = NUM2ULONG(len);
	return INT2NUM(s_push(pushme, size));
}

static VALUE rb_set_needreserved(VALUE self, VALUE need){
	int needreserved;

	needreserved = NUM2INT(need);
	return INT2NUM(s_set_needreserved(needreserved));
}

static VALUE rb_block_start(VALUE self, VALUE name){
	char *blockname;

	blockname = STR2CSTR(name);
	return INT2NUM(s_block_start(blockname));
}

static VALUE rb_binary_block_size_word_bigendian(VALUE self, VALUE name){
	char *blockname;

	blockname = STR2CSTR(name);
	return INT2NUM(s_binary_block_size_word_bigendian(blockname));
}

static VALUE rb_block_end(VALUE self, VALUE name){
	char *blockname;

	blockname = STR2CSTR(name);
	return INT2NUM(s_block_end(blockname));
}

static VALUE rb_print_buffer(VALUE self){
	s_print_buffer();
	return Qnil;
}

static VALUE rb_printf_buffer(VALUE self){
	s_printf_buffer();
	return Qnil;
}

static VALUE rb_get_size(VALUE self){
	return INT2NUM(s_get_size());
}

static VALUE rb_get_databuf(VALUE self){
	return rb_str_new2(s_get_databuf());
}

static VALUE rb_spike_send(VALUE self){
	return INT2NUM(spike_send());
}

static VALUE rb_send_tcp(VALUE self, VALUE hostname, VALUE portnum){
	char *host;
	int port;

	host = STR2CSTR(hostname);
	port = NUM2INT(portnum);

	return INT2NUM(spike_send_tcp(host, port));
}

static VALUE rb_bigword(VALUE self, VALUE word){
	unsigned int aword;

	aword = NUM2INT(word);
	return INT2NUM(s_bigword(aword));
}

static VALUE rb_binary_block_size_word_bigendian_plussome(VALUE self, VALUE bname, VALUE some){
	char *blockname;
	long plussome;

	blockname = STR2CSTR(bname);
	plussome = NUM2INT(some);

	return INT2NUM(s_binary_block_size_word_bigendian_plussome(blockname, plussome));
}

static VALUE rb_binary_block_size_byte_mult(VALUE self, VALUE bname, VALUE rmult){
	char *blockname;
	double mult;

	blockname = STR2CSTR(bname);
	mult = NUM2DBL(rmult); 

	return INT2NUM(s_binary_block_size_byte_mult(blockname, mult));
}

static VALUE rb_binary_block_size_word_bigendian_mult(VALUE self, VALUE bname, VALUE rmult){
	char *blockname;
        double mult;
        
        blockname = STR2CSTR(bname);
        mult = NUM2DBL(rmult); 
        
        return INT2NUM(s_binary_block_size_word_bigendian_mult(blockname, mult));
}

static VALUE rb_binary_block_size_word_intel_mult_plus(VALUE self, VALUE bname, VALUE some, VALUE rmult){
        char *blockname;
	long plussome;
        double mult;

        blockname = STR2CSTR(bname);
	plussome = NUM2LONG(some);
        mult = NUM2DBL(rmult);

        return INT2NUM(s_binary_block_size_word_intel_mult_plus(blockname, plussome, mult));
}

static VALUE rb_binary_block_size_intel_halfword_mult(VALUE self, VALUE bname, VALUE rmult){
        char *blockname;
        double mult;

        blockname = STR2CSTR(bname);
        mult = NUM2DBL(rmult);
        
        return INT2NUM(s_binary_block_size_intel_halfword_mult(blockname, mult));
}

static VALUE rb_xdr_string(VALUE self, VALUE string){
	unsigned char *astring;

	astring = STR2CSTR(string);
	return INT2NUM(s_xdr_string(astring));
}

static VALUE rb_binary_repeat(VALUE self, VALUE string, VALUE rtimes){
	char *instring;
	int times;

	instring = STR2CSTR(string);
	times = NUM2INT(rtimes);

	return INT2NUM(s_binary_repeat(instring, times));
}

static VALUE rb_string_repeat(VALUE self, VALUE string, VALUE rtimes){
        char *instring;
        int times;

        instring = STR2CSTR(string);
        times = NUM2INT(rtimes);

        return INT2NUM(s_string_repeat(instring, times));
}

static VALUE rb_string_lf(VALUE self, VALUE string){
	char *instring;

	instring = STR2CSTR(string);

	return INT2NUM(s_string_lf(instring));
}

static VALUE rb_ioal(VALUE self, VALUE rmyint){
	unsigned long myint;

	myint = NUM2ULONG(rmyint);

	return INT2NUM(ioal(myint));
}

static VALUE rb_ioas(VALUE self, VALUE rmyint){
        unsigned short myint;

        myint = NUM2UINT(rmyint);

        return INT2NUM(ioas(myint));
}

static VALUE rb_intel_order(VALUE self, VALUE buf, VALUE len){
	char *buffer;
	int length;

	buffer = STR2CSTR(buf);
	length = NUM2INT(len);

	intel_order(buffer, length);
	return Qnil;
}

static VALUE rb_intelword(VALUE self, VALUE word){
	unsigned int aword;

	aword = NUM2UINT(word);

	return INT2NUM(s_intelword(aword));
}

static VALUE rb_intelhalfword(VALUE self, VALUE rshort){
	unsigned short ashort;

	ashort = NUM2UINT(rshort);

	return INT2NUM(s_intelhalfword(ashort));
}

static VALUE rb_binary_block_size_intel_halfword(VALUE self, VALUE bname){
	char *blockname;
	
	blockname = STR2CSTR(bname);

	return INT2NUM(s_binary_block_size_intel_halfword(blockname));
}

static VALUE rb_binary_block_size_halfword_bigendian(VALUE self, VALUE bname){
        char *blockname;

        blockname = STR2CSTR(bname);

        return INT2NUM(s_binary_block_size_halfword_bigendian(blockname));
}

static VALUE rb_binary_block_size_intel_halfword_plus(VALUE self, VALUE bname, VALUE rplus){
	char *blockname;
	long plus;

	blockname = STR2CSTR(bname);
	plus = NUM2LONG(rplus);

	return INT2NUM(s_binary_block_size_intel_halfword_plus(blockname, plus));
}

static VALUE rb_binary_block_size_byte_plus(VALUE self, VALUE bname, VALUE rplus){
	char *blockname;
        long plus;

        blockname = STR2CSTR(bname);
        plus = NUM2LONG(rplus);

        return INT2NUM(s_binary_block_size_byte_plus(blockname, plus));
} 


static VALUE rb_binary_block_size_byte(VALUE self, VALUE bname){
	char *blockname;

	blockname = STR2CSTR(bname);

	return INT2NUM(s_binary_block_size_byte(blockname));
}

static VALUE rb_tcp_accept(VALUE self, VALUE fd){
	int listenfd;

	listenfd = NUM2INT(fd);

	return INT2NUM(s_tcp_accept(listenfd));
}

static VALUE rb_close_udp(VALUE self){
	s_close_udp();
	return Qnil;
}	

static VALUE rb_fd_wait(VALUE self){
	return INT2NUM(s_fd_wait());
}

static VALUE rb_fd_clear(VALUE self){
	s_fd_clear();
	return Qnil;
}

static VALUE rb_string_or_env(VALUE self, VALUE evar, VALUE rvar){
	unsigned char *envvar;
	unsigned char *realvar;

	envvar = STR2CSTR(evar);
	realvar = STR2CSTR(rvar);

	s_string_or_env(envvar, realvar);
	
	return Qnil;
}

static VALUE rb_string_variables(VALUE self, VALUE split, VALUE vars){
	unsigned char *splitchar, *variables;

	splitchar = STR2CSTR(split);
	variables = STR2CSTR(vars);

	s_string_variables(splitchar, variables);

	return Qnil;
}

static VALUE rb_string_variable(VALUE self, VALUE var){
	unsigned char *variable;

	variable = STR2CSTR(var);

	s_string_variable(variable);

	return Qnil;
}

static VALUE rb_reset_fuzzvariable(VALUE self){
	s_reset_fuzzvariable();
	return Qnil;
}

static VALUE rb_setfirstvariable(VALUE self){
	s_setfirstvariable();
	return Qnil;
}

static VALUE rb_scan_for_variable(VALUE self, VALUE buf, VALUE startdel, VALUE enddel){
	unsigned char *buffer, *startdelim, *enddelim;

	buffer = STR2CSTR(buf);
	startdelim = STR2CSTR(startdel);
	enddelim = STR2CSTR(enddel);

	return rb_str_new2(s_scan_for_variable(buffer, startdelim, enddelim));
}

static VALUE rb_getcurrentspike(VALUE klass){
        struct spike *s;

        s = getcurrentspike();
        return Data_Wrap_Struct(klass, rspike_mark, rspike_free, s);	
}

static VALUE rb_get_spike_fd(VALUE self){
	return INT2NUM(get_spike_fd());
}

static VALUE rb_set_unicode(VALUE self, VALUE rms){
	int ms;

	ms = NUM2INT(rms);
	s_set_unicode(ms);
	return Qnil;
}

static VALUE rb_update_listeners(VALUE self, VALUE rsize){
	int size;

	size = NUM2INT(rsize);
	s_update_listeners(size);
	return Qnil;
}

static VALUE rb_read_packet(VALUE self){
	s_read_packet();
	return Qnil;
}

static VALUE rb_get_max_fuzzstring(VALUE self){
	return INT2NUM(s_get_max_fuzzstring());
}

static VALUE rb_get_fuzzstring(VALUE self, VALUE i){
	int index;

	index = NUM2INT(i);
	return rb_str_new2(s_get_fuzzstring(index));
}

static VALUE rb_get_random_fuzzstring(VALUE self){
	return rb_str_new2(s_get_random_fuzzstring());
}

static VALUE rb_read_bigendian_word_packet(VALUE self, VALUE buffer){
	char *buf;

	buf = STR2CSTR(buffer);
	return INT2NUM(s_read_bigendian_word_packet(buf));
}

static VALUE rb_cstring(VALUE self, VALUE string){
	char *instring;

	instring = STR2CSTR(string);
	s_cstring(instring);
	return Qnil;
}

static VALUE rb_unistring(VALUE self, VALUE string){
	char *instring;

	instring = STR2CSTR(string);
        s_unistring(instring);
        return Qnil;
}

void Init_rspike() {
	rb_cSpike = rb_define_class("Spike", rb_cObject);
	rb_define_alloc_func(rb_cSpike, rspike_allocate);
	rb_define_method(rb_cSpike, "set_spike", rb_set_spike, 0);
	rb_define_method(rb_cSpike, "init_fuzz", rb_init_fuzzing, 0);
	rb_define_method(rb_cSpike, "didlastvar?", rb_didlastvariable, 0);
	rb_define_method(rb_cSpike, "reset_fuzzstr", rb_reset_fuzzstring, 0);
	rb_define_method(rb_cSpike, "inc_fuzzvar", rb_increment_fuzzvar, 0);
	rb_define_method(rb_cSpike, "inc_fuzzstr", rb_increment_fuzzstring, 0);
	rb_define_method(rb_cSpike, "didlastfuzzstr?", rb_didlastfuzzstring, 0);	
	rb_define_method(rb_cSpike, "clear", rb_spikeclear, 0);
	rb_define_method(rb_cSpike, "connect_tcp", rb_connect_tcp, 2);
	rb_define_method(rb_cSpike, "readline", rb_readline, 0);
	rb_define_method(rb_cSpike, "parse", rb_parse, 1);
	rb_define_method(rb_cSpike, "close_tcp", rb_close_tcp, 0);
	rb_define_method(rb_cSpike, "send_lines", rb_send_lines, 0);
	rb_define_method(rb_cSpike, "string", rb_string, 1);
	rb_define_method(rb_cSpike, "blocksize_str", rb_blocksize_string, 2);
	rb_define_method(rb_cSpike, "binary", rb_binary, 1);
	rb_define_method(rb_cSpike, "push", rb_push, 2);
	rb_define_method(rb_cSpike, "need_reserved", rb_set_needreserved, 1);
	rb_define_method(rb_cSpike, "block_start", rb_block_start, 1);
	rb_define_method(rb_cSpike, "binary_block_size_word_bigendian", rb_binary_block_size_word_bigendian, 1);
	rb_define_method(rb_cSpike, "block_end", rb_block_end, 1);
	rb_define_method(rb_cSpike, "print_buf", rb_print_buffer, 0);
	rb_define_method(rb_cSpike, "printf_buf", rb_printf_buffer, 0);
	rb_define_method(rb_cSpike, "get_size", rb_get_size, 0);
	rb_define_method(rb_cSpike, "get_databuf", rb_get_databuf, 0);
	rb_define_method(rb_cSpike, "send", rb_spike_send, 0);
	rb_define_method(rb_cSpike, "send_tcp", rb_send_tcp, 2);
	rb_define_method(rb_cSpike, "bigword", rb_bigword, 1);
	rb_define_method(rb_cSpike, "binary_block_size_word_bigendian_plus", rb_binary_block_size_word_bigendian_plussome, 2);
	rb_define_method(rb_cSpike, "binary_block_size_byte_mult", rb_binary_block_size_byte_mult, 2);
	rb_define_method(rb_cSpike, "binary_block_size_word_bigendian_mult", rb_binary_block_size_word_bigendian_mult, 2);
	rb_define_method(rb_cSpike, "binary_block_size_word_intel_mult_plus", rb_binary_block_size_word_intel_mult_plus, 3);
	rb_define_method(rb_cSpike, "binary_block_size_intel_halfword_mult", rb_binary_block_size_intel_halfword_mult, 2);
	rb_define_method(rb_cSpike, "xdr_string", rb_xdr_string, 1);
	rb_define_method(rb_cSpike, "binary_repeat", rb_binary_repeat, 2);
	rb_define_method(rb_cSpike, "string_repeat", rb_string_repeat, 2);
	rb_define_method(rb_cSpike, "string_lf", rb_string_lf, 1);
	rb_define_method(rb_cSpike, "ioal", rb_ioal, 1);
	rb_define_method(rb_cSpike, "ioas", rb_ioas, 1);
	rb_define_method(rb_cSpike, "intel_order", rb_intel_order, 2);
	rb_define_method(rb_cSpike, "rb_intelword", rb_intelword, 1);
	rb_define_method(rb_cSpike, "intelhalfword", rb_intelhalfword, 1);
	rb_define_method(rb_cSpike, "binary_block_size_intel_halfword", rb_binary_block_size_intel_halfword, 1);
	rb_define_method(rb_cSpike, "binary_block_size_halfword_bigendian", rb_binary_block_size_halfword_bigendian, 1);
	rb_define_method(rb_cSpike, "binary_block_size_intel_halfword_plus", rb_binary_block_size_intel_halfword_plus, 2);
	rb_define_method(rb_cSpike, "binary_block_size_byte", rb_binary_block_size_byte, 1);
	rb_define_method(rb_cSpike, "binary_block_size_byte_plus", rb_binary_block_size_byte_plus, 2);
	rb_define_method(rb_cSpike, "tcp_accept", rb_tcp_accept, 1);
	rb_define_method(rb_cSpike, "close_udp", rb_close_udp, 0);
	rb_define_method(rb_cSpike, "fd_wait", rb_fd_wait, 0);
	rb_define_method(rb_cSpike, "fd_clear", rb_fd_clear, 0);
	rb_define_method(rb_cSpike, "string_or_env", rb_string_or_env, 2);
	rb_define_method(rb_cSpike, "string_variables", rb_string_variables, 2);
	rb_define_method(rb_cSpike, "string_variable", rb_string_variable, 1);
	rb_define_method(rb_cSpike, "reset_fuzzvariable", rb_reset_fuzzvariable, 0);
	rb_define_method(rb_cSpike, "setfirstvariable", rb_setfirstvariable, 0);
	rb_define_method(rb_cSpike, "scan_for_variable", rb_scan_for_variable, 3);
	rb_define_method(rb_cSpike, "getcurrentspike", rb_getcurrentspike, 0);
	rb_define_method(rb_cSpike, "get_spike_fd", rb_get_spike_fd, 0);
	rb_define_method(rb_cSpike, "set_unicode", rb_set_unicode, 1);
	rb_define_method(rb_cSpike, "update_listeners", rb_update_listeners, 1);
	rb_define_method(rb_cSpike, "read_packet", rb_read_packet, 0);
	rb_define_method(rb_cSpike, "get_max_fuzzstring", rb_get_max_fuzzstring, 0);
	rb_define_method(rb_cSpike, "get_fuzzstring", rb_get_fuzzstring, 1);
	rb_define_method(rb_cSpike, "get_random_fuzzstring", rb_get_random_fuzzstring, 0);
	rb_define_method(rb_cSpike, "read_bigendian_word_packet", rb_read_bigendian_word_packet, 1);
	rb_define_method(rb_cSpike, "cstring", rb_cstring, 1);
	rb_define_method(rb_cSpike, "unistring", rb_unistring, 1);
}

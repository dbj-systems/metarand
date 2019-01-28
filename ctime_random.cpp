

// as an example, one can call bellow like this
// constexpr inline unsigned long hash_code =
//	dbj::util::hash(__FILE__);
constexpr inline unsigned long hash(const char *str)
{
	unsigned long hash = 5381;
	int c = 0;
	while ((c = *str++))
		hash = ((hash << 5) + hash) + c; // hash * 33 + c 
	return hash;
}

constexpr inline unsigned long  hashed_timestamp = hash(__TIMESTAMP__) ;

/*  Global static variables:
	(the seed changes on every minute) */
static unsigned long
z = hashed_timestamp,
w = 521288629 * hashed_timestamp, 
jsr = 123456789 * hashed_timestamp,
jcong = 380116160 * hashed_timestamp;

#define znew  ((z=36969*(z&65535)+(z>>16))<<16)
#define wnew  ((w=18000*(w&65535)+(w>>16))&65535)
#define MWC   (znew+wnew)
#define SHR3  (jsr=(jsr=(jsr=jsr^(jsr<<17))^(jsr>>13))^(jsr<<5))
#define CONG  (jcong=69069*jcong+1234567)
//#define KISS  (MWC+CONG)+SHR3)
#define KISS  (CONG)


// no can do
extern "C" unsigned long compile_time_random () {
	static unsigned long rez{ KISS };
	return  (rez < 0 ? -1 * rez : rez );
}
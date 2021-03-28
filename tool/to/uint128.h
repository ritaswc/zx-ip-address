#ifndef UINT128_H_
#define UINT128_H_

struct uint128_t {
	unsigned __int64 lo, hi;
	uint128_t() : lo(0), hi(0) {}
	uint128_t(const unsigned char n) : lo(n), hi(0) {}
	uint128_t(const unsigned short n) : lo(n), hi(0) {}
	uint128_t(const unsigned int n) : lo(n), hi(0) {}
	uint128_t(const unsigned long n) : lo(n), hi(0) {}
	uint128_t(const unsigned __int64 n) : lo(n), hi(0) {}
	uint128_t(const char n) {
		if (n < 0) {
			lo = -n;
			hi = -1;
		} else {
			lo = n;
			hi = 0;
		}
	}
	uint128_t(const short n) {
		if (n < 0) {
			lo = -n;
			hi = -1;
		} else {
			lo = n;
			hi = 0;
		}
	}
	uint128_t(const int n) {
		if (n < 0) {
			lo = -n;
			hi = -1;
		} else {
			lo = n;
			hi = 0;
		}
	}
	uint128_t(const long n) {
		if (n < 0) {
			lo = -n;
			hi = -1;
		} else {
			lo = n;
			hi = 0;
		}
	}
	uint128_t(const __int64 n){
		if (n < 0) {
			lo = -n;
			hi = -1;
		} else {
			lo = n;
			hi = 0;
		}
	}
	uint128_t operator + (const uint128_t n) const {
		uint128_t r;
		r.lo = lo + n.lo;
		r.hi = hi + n.hi;
		if (r.lo < lo) r.hi++;
		return r;
	}
	uint128_t operator - (const uint128_t n) const {
		uint128_t r;
		r.lo = lo - n.lo;
		r.hi = hi - n.hi;
		if (r.lo > lo) r.hi--;
		return r;
	}
	uint128_t operator << (const int n) const {
		uint128_t r = *this;
		int i;
		if (n >= 128 || n < 0) return 0;
		for (i=0; i<n; i++) {
			r.hi <<= 1;
			if (r.lo & 0x8000000000000000) {
				r.hi |= 1;
			}
			r.lo <<= 1;
		}
		return r;
	}
	uint128_t operator >> (const int n) const {
		uint128_t r = *this;
		int i;
		if (n >= 128 || n < 0) return 0;
		for (i=0; i<n; i++) {
			r.lo >>= 1;
			if (r.hi & 1) {
				r.lo |= 0x8000000000000000;
			}
			r.hi >>= 1;
		}
		return r;
	}
	uint128_t operator & (const uint128_t n) const {
		uint128_t r;
		r.lo = lo & n.lo;
		r.hi = hi & n.hi;
		return r;
	}
	uint128_t operator | (const uint128_t n) const {
		uint128_t r;
		r.lo = lo | n.lo;
		r.hi = hi | n.hi;
		return r;
	}
	uint128_t operator ^ (const uint128_t n) const {
		uint128_t r;
		r.lo = lo ^ n.lo;
		r.hi = hi ^ n.hi;
		return r;
	}
	uint128_t operator = (const uint128_t n) {
		lo = n.lo;
		hi = n.hi;
		return *this;
	}
	uint128_t operator += (const uint128_t n) {
		*this = operator +(n);
		return *this;
	}
	uint128_t operator -= (const uint128_t n) {
		*this = operator -(n);
		return *this;
	}
	uint128_t operator <<= (const int n) {
		*this = operator <<(n);
		return *this;
	}
	uint128_t operator >>= (const int n) {
		*this = operator >>(n);
		return *this;
	}
	uint128_t operator &= (const uint128_t n) {
		*this = operator &(n);
		return *this;
	}
	uint128_t operator |= (const uint128_t n) {
		*this = operator |(n);
		return *this;
	}
	uint128_t operator ^= (const uint128_t n) {
		*this = operator ^(n);
		return *this;
	}
	bool operator < (const uint128_t n) const {
		if (hi < n.hi)
			return true;
		else if (hi == n.hi && lo < n.lo)
			return true;
		else
			return false;
	}
	bool operator > (const uint128_t n) const {
		if (hi > n.hi)
			return true;
		else if (hi == n.hi && lo > n.lo)
			return true;
		else
			return false;
	}
	bool operator <= (const uint128_t n) const {
		if (hi < n.hi)
			return true;
		else if (hi == n.hi && lo <= n.lo)
			return true;
		else
			return false;
	}
	bool operator >= (const uint128_t n) const {
		if (hi > n.hi)
			return true;
		else if (hi == n.hi && lo >= n.lo)
			return true;
		else
			return false;
	}
	bool operator == (const uint128_t n) const {
		if (hi == n.hi && lo == n.lo)
			return true;
		else
			return false;
	}
	bool operator != (const uint128_t n) const {
		if (hi != n.hi || lo != n.lo)
			return true;
		else
			return false;
	}

	uint128_t num() {
		return *this;
	}
	unsigned __int64 num64() const {
		return hi;
	}
	unsigned short *n() const {
		return (unsigned short *)&lo;
	}
};

#endif

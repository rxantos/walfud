

// wGdtHelper.cpp
//

#include "wGdtHelper.h"
#include <string>
using namespace std;

GDT_Entry::GDT_Entry() : m_addr(0), m_limit(0), m_type(0), m_s(0), m_dpl(0), m_p(0), m_avl(0), m_l(0), m_db(0), m_g(0) {}
GDT_Entry::GDT_Entry(uint32_t bit_0_32, uint32_t bit_32_64) { set_0_32(bit_0_32), set_32_64(bit_32_64); }
GDT_Entry::GDT_Entry(uint64_t bit_0_64) { set_0_64(bit_0_64); }
GDT_Entry::~GDT_Entry() {}

// Interface.
void GDT_Entry::setAddr(uint32_t addr) { m_addr = addr; }
void GDT_Entry::setLimit(uint32_t limit) { m_limit = limit & 0x000fffff; }
void GDT_Entry::setType(uint32_t type) { m_type = type & 0x0f; }
void GDT_Entry::setS(uint32_t s) { m_s = s & 0x01; }
void GDT_Entry::setDPL(uint32_t dpl) { m_dpl = dpl & 0x03; }
void GDT_Entry::setP(uint32_t p) { m_p = p & 0x01; }
void GDT_Entry::setAVL(uint32_t avl) { m_avl = avl & 0x01; }
void GDT_Entry::setL(uint32_t l) { m_l = l & 0x01; }
void GDT_Entry::setDB(uint32_t db) { m_db = db & 0x01; }
void GDT_Entry::setG(uint32_t g) { m_g = g & 0x01; }
uint32_t GDT_Entry::getAddr() const { return m_addr; }
uint32_t GDT_Entry::getLimit() const { return m_limit; }
uint32_t GDT_Entry::getType() const { return m_type; }
uint32_t GDT_Entry::getS() const { return m_s; }
uint32_t GDT_Entry::getDPL() const { return m_dpl; }
uint32_t GDT_Entry::getP() const { return m_p; }
uint32_t GDT_Entry::getAVL() const { return m_avl; }
uint32_t GDT_Entry::getL() const { return m_l; }
uint32_t GDT_Entry::getDB() const { return m_db; }
uint32_t GDT_Entry::getG() const { return m_g; }

void GDT_Entry::set_0_32(uint32_t bit_0_32)
{
	m_limit = bit_0_32 & 0x0000ffff;
	m_addr = (m_addr & 0xffff0000) | (bit_0_32 >> 16);
}
void GDT_Entry::set_32_64(uint32_t bit_32_64)
{
	m_addr = (m_addr & 0x0000ffff) | ((bit_32_64 & 0x000000ff) << 16) | (bit_32_64 & 0xff000000);
	m_type = (bit_32_64 & 0x00000f00) >> 8;
	m_s = (bit_32_64 & 0x00001000) >> 12;
	m_dpl = (bit_32_64 & 0x00006000) >> 13;
	m_p = (bit_32_64 & 0x00008000) >> 15;
	m_limit = (m_limit & 0x00ffff) | (bit_32_64 & 0x000f0000);
	m_avl = (bit_32_64 & 0x00100000) >> 20;
	m_l = (bit_32_64 & 0x00200000) >> 21;
	m_db = (bit_32_64 & 0x00400000) >> 22;
	m_g = (bit_32_64 & 0x00800000) >> 23;
}
void GDT_Entry::set_0_64(uint64_t bit_0_64) { set_0_32(static_cast<uint32_t>(bit_0_64)), set_32_64(bit_0_64 >> 32); }
uint32_t GDT_Entry::get_0_32() const { return (m_limit & 0x00ffff) | ((m_addr & 0x0000ffff) << 16); }
uint32_t GDT_Entry::get_32_64() const
{
	uint32_t res = 0;

	res |= (m_addr & 0xff000000) | ((m_addr & 0x00ff0000) >> 16);
	res |= m_g << 23;
	res |= m_db << 22;
	res |= m_l << 21;
	res |= m_avl << 20;
	res |= (m_limit & 0xff0000);
	res |= m_p << 15;
	res |= m_dpl << 13;
	res |= m_s << 12;
	res |= m_type << 8;

	return res;
}
uint64_t GDT_Entry::get_0_64() const { return (static_cast<uint64_t>(get_32_64()) << 32) | get_0_32(); }
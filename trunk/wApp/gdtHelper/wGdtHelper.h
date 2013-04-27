

// wGdtHelper.h
// 

#ifndef W_GDT_HELPER_H
#define W_GDT_HELPER_H

#include <stdint.h>

class GDT_Entry
{
	// data.
	uint32_t m_addr		:	32;
	uint32_t m_limit	:	20;

	uint32_t m_type		:	4,
			 m_s		:	1,
			 m_dpl		:	2,
			 m_p		:	1, 

			 m_avl		:	1,
			 m_l		:	1, 
			 m_db		:	1,
			 m_g		:	1;

public:
	GDT_Entry();
	GDT_Entry(uint32_t bit_0_32, uint32_t bit_32_64);
	GDT_Entry(uint64_t bit_0_64);
	~GDT_Entry();

public:
	// Interface.
	void setAddr(uint32_t addr);
	void setLimit(uint32_t limit);
	void setType(uint32_t type);
	void setS(uint32_t s);
	void setDPL(uint32_t dpl);
	void setP(uint32_t p);
	void setAVL(uint32_t avl);
	void setL(uint32_t l);
	void setDB(uint32_t db);
	void setG(uint32_t g);
	uint32_t getAddr() const;
	uint32_t getLimit() const;
	uint32_t getType() const;
	uint32_t getS() const;
	uint32_t getDPL() const;
	uint32_t getP() const;
	uint32_t getAVL() const;
	uint32_t getL() const;
	uint32_t getDB() const;
	uint32_t getG() const;

	void set_0_32(uint32_t bit_0_32);
	void set_32_64(uint32_t bit_32_64);
	void set_0_64(uint64_t bit_0_64);
	uint32_t get_0_32() const;
	uint32_t get_32_64() const;
	uint64_t get_0_64() const;
};

#endif // W_GDT_HELPER_H
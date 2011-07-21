/*

	Copyright (c) 2011, Coleman Stavish
	All rights reserved.
	
	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:
		* Redistributions of source code must retain the above copyright
			notice, this list of conditions and the following disclaimer.
		* Redistributions in binary form must reproduce the above copyright
			notice, this list of conditions and the following disclaimer in the
			documentation and/or other materials provided with the distribution.
		* Neither the name of Coleman Stavish nor the
			names of contributors may be used to endorse or promote products
			derived from this software without specific prior written permission.
	
	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
	DISCLAIMED. IN NO EVENT SHALL COLEMAN STAVISH BE LIABLE FOR ANY
	DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
	
*/

#include <stdint.h>

struct cs_knode {
	char *key;
	void *val;
	struct cs_knode *next;
};

struct cs_hash_tab {
	uint32_t size;
	uint32_t count;
	float max_load;
	float min_load;
	struct cs_knode **buckets;
	void (*cleanup)(const char *, void *);
	uint32_t (*hash)(const char *, uint32_t);
};

typedef struct cs_knode	cs_knode;
typedef struct cs_hash_tab cs_hash_tab;

/**
 * cs_hash_create - create hash table
 *
 * @return - reference to a newly allocated, empty hash table 
 *
 * NOTE: 8 buckets allocated by default, min_load set to 0.25, max_load set to 0.75
 *
 */
cs_hash_tab *cs_hash_create(void);


/**
 * cs_hash_create_kv - create hash table with the specified key-value pairs
 *
 * @param key - first key
 * @param val - first value
 * @param ... - NULL-terminated list of additional key-value pairs
 *
 * @return - a reference to a newly allocated hash table, populated with the specified key-value pairs
 *
 */
cs_hash_tab *cs_hash_create_kv(const char *key, void *val, ...);


/**
 * cs_hash_create_opt - create hash table with the specified options
 *
 * @param initial		- initial number of buckets to allocate
 * @param max_load	- maximum element-bucket ratio before the table is resized and keys are rehashed
 * @param min_load	- minimum ''
 *
 * @return - a reference to a newly allocated hash table, populated with the specified key-value pairs
 *
 */
cs_hash_tab *cs_hash_create_opt(uint32_t initial, float max_load, float min_load);


/**
 * cs_hash_set - map the specified key to the specified value
 *
 * @param tab - reference to the hash table upon wherein the key will be mapped
 * @param key - 
 * @param val -
 *
 * NOTE: if tab already has a value for key, then it is changed to val
 *
 */
void cs_hash_set(cs_hash_tab *tab, const char *key, void *val);


/**
 * cs_hash_get - get the value for the specified key
 *
 * @param tab -
 * @param key -
 *
 */
void *cs_hash_get(cs_hash_tab *tab, const char *key);


/**
 * cs_hash_del - delete the value for the specified key
 *
 * @param tab -
 * @param key -
 *
 * @return - the value which was unmapped
 *
 */
void *cs_hash_del(cs_hash_tab *tab, const char *key);


/**
 * cs_hash_destroy - destroy the specified hash table in its entirity
 *
 * @param tab -
 *
 * NOTE: if it is not NULL, tab->cleanup will be called for each value in the hash table
 *
 */
void cs_hash_destroy(cs_hash_tab *tab);

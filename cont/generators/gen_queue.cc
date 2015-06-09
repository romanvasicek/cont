
#define QUEUE_INIT() \
{\
printf(\
"inline void %s::init()\n"\
"{/*{{{*/\n"\
"   size = 0;\n"\
"   used = 0;\n"\
"   begin = 0;\n"\
"   data = NULL;\n"\
"}/*}}}*/\n"\
"\n"\
,IM_STRUCT_NAME);\
}

#define QUEUE_INIT_SIZE() \
{\
printf(\
"inline void %s::init_size(unsigned a_size)\n"\
"{/*{{{*/\n"\
"   init();\n"\
"   copy_resize(a_size);\n"\
"}/*}}}*/\n"\
"\n"\
,IM_STRUCT_NAME);\
}

#define QUEUE_CLEAR() \
{\
   if (!(TYPE_NUMBER & c_type_dynamic)) {\
printf(\
"inline void %s::clear()\n"\
,IM_STRUCT_NAME);\
   }\
   else {\
printf(\
"void %s::clear()\n"\
,IM_STRUCT_NAME);\
   }\
printf(\
"{/*{{{*/\n"\
"   if (data != NULL) {\n"\
);\
   if (TYPE_NUMBER & c_type_dynamic) {\
printf(\
"      %s *ptr = data;\n"\
"      %s *ptr_end = ptr + size;\n"\
"\n"\
"      do {\n"\
"         ptr->clear();\n"\
"      } while(++ptr < ptr_end);\n"\
"\n"\
,TYPE_NAME,TYPE_NAME);\
   }\
printf(\
"      cfree(data);\n"\
"   }\n"\
"\n"\
"   init();\n"\
"}/*}}}*/\n"\
"\n"\
);\
}

#define QUEUE_FLUSH() \
{\
printf(\
"inline void %s::flush()\n"\
"{/*{{{*/\n"\
"   copy_resize(used);\n"\
"}/*}}}*/\n"\
"\n"\
,IM_STRUCT_NAME);\
}

#define QUEUE_FLUSH_ALL() \
{\
   if (!(TYPE_NUMBER & c_type_flushable)) {\
printf(\
"inline void %s::flush_all()\n"\
,IM_STRUCT_NAME);\
   }\
   else {\
printf(\
"void %s::flush_all()\n"\
,IM_STRUCT_NAME);\
   }\
printf(\
"{/*{{{*/\n"\
"   copy_resize(used);\n"\
);\
   if (TYPE_NUMBER & c_type_flushable) {\
printf(\
"\n"\
"   if (used == 0) return;\n"\
"\n"\
"   %s *ptr = data;\n"\
"   %s *ptr_end = ptr + used;\n"\
"\n"\
"   do {\n"\
"      ptr->flush_all();\n"\
"   } while(++ptr < ptr_end);\n"\
,TYPE_NAME,TYPE_NAME);\
   }\
printf(\
"}/*}}}*/\n"\
"\n"\
);\
}

#define QUEUE_SWAP() \
{\
printf(\
"inline void %s::swap(%s &second)\n"\
"{/*{{{*/\n"\
"   unsigned tmp_unsigned = size;\n"\
"   size = second.size;\n"\
"   second.size = tmp_unsigned;\n"\
"\n"\
"   tmp_unsigned = used;\n"\
"   used = second.used;\n"\
"   second.used = tmp_unsigned;\n"\
"\n"\
"   tmp_unsigned = begin;\n"\
"   begin = second.begin;\n"\
"   second.begin = tmp_unsigned;\n"\
"\n"\
"   %s *tmp_data = data;\n"\
"   data = second.data;\n"\
"   second.data = tmp_data;\n"\
"}/*}}}*/\n"\
"\n"\
,IM_STRUCT_NAME,IM_STRUCT_NAME,TYPE_NAME);\
}

#define QUEUE_INSERT() \
{\
   if (TYPE_NUMBER & c_type_basic) {\
printf(\
"inline void %s::insert(%s a_value)\n"\
,IM_STRUCT_NAME,TYPE_NAME);\
   }\
   else {\
printf(\
"inline void %s::insert(%s &a_value)\n"\
,IM_STRUCT_NAME,TYPE_NAME);\
   }\
printf(\
"{/*{{{*/\n"\
"   if (used >= size) {\n"\
"      copy_resize((size << 1) + c_array_add);\n"\
"   }\n"\
"\n"\
"   if (begin + used >= size) {\n"\
"      data[begin + used - size] = a_value;\n"\
"   }\n"\
"   else {\n"\
"      data[begin + used] = a_value;\n"\
"   }\n"\
"\n"\
"   used++;\n"\
"}/*}}}*/\n"\
"\n"\
);\
}

#define QUEUE_INSERT_BLANK() \
{\
printf(\
"inline void %s::insert_blank()\n"\
"{/*{{{*/\n"\
"   if (used >= size) {\n"\
"      copy_resize((size << 1) + c_array_add);\n"\
"   }\n"\
"\n"\
"   used++;\n"\
"}/*}}}*/\n"\
"\n"\
,IM_STRUCT_NAME);\
}

#define QUEUE_NEXT() \
{\
printf(\
"inline %s &%s::next()\n"\
"{/*{{{*/\n"\
"   debug_assert(used > 0);\n"\
"\n"\
"   unsigned ret_idx = begin;\n"\
"\n"\
"   if (++begin >= size) {\n"\
"      begin = 0;\n"\
"   }\n"\
"\n"\
"   used--;\n"\
"   \n"\
"   return data[ret_idx];\n"\
"}/*}}}*/\n"\
"\n"\
,TYPE_NAME,IM_STRUCT_NAME);\
}

#define QUEUE_LAST() \
{\
printf(\
"inline %s &%s::last()\n"\
"{/*{{{*/\n"\
"   debug_assert(used > 0);\n"\
"\n"\
"   if (begin + (used - 1) >= size) {\n"\
"      return data[begin + (used - 1) - size];\n"\
"   }\n"\
"   else {\n"\
"      return data[begin + (used - 1)];\n"\
"   }\n"\
"}/*}}}*/\n"\
"\n"\
,TYPE_NAME,IM_STRUCT_NAME);\
}

#define QUEUE_COPY_RESIZE() \
{\
printf(\
"void %s::copy_resize(unsigned a_size)\n"\
"{/*{{{*/\n"\
"   debug_assert(a_size >= used);\n"\
"\n"\
"   %s *n_data;\n"\
"\n"\
"   if (a_size == 0) {\n"\
"      n_data = NULL;\n"\
"   }\n"\
"   else {\n"\
"      n_data = (%s *)cmalloc(a_size*sizeof(%s));\n"\
,IM_STRUCT_NAME,TYPE_NAME,TYPE_NAME,TYPE_NAME);\
   if (TYPE_NUMBER & c_type_dynamic) {\
printf(\
"\n"\
"      if (a_size > used) {\n"\
"         %s *ptr = n_data + used;\n"\
"         %s *ptr_end = n_data + a_size;\n"\
"\n"\
"         do {\n"\
"            ptr->init();\n"\
"         } while(++ptr < ptr_end);\n"\
"      }\n"\
,TYPE_NAME,TYPE_NAME);\
   }\
printf(\
"   }\n"\
"\n"\
"   if (used != 0) {\n"\
"      unsigned fir_cnt;\n"\
"      unsigned sec_cnt;\n"\
"\n"\
"      if (begin + used > size) {\n"\
"         sec_cnt = begin + used - size;\n"\
"         fir_cnt = used - sec_cnt;\n"\
"      }\n"\
"      else {\n"\
"         fir_cnt = used;\n"\
"         sec_cnt = 0;\n"\
"      }\n"\
"\n"\
"      memcpy(n_data,data + begin,fir_cnt*sizeof(%s));\n"\
"\n"\
"      if (sec_cnt != 0) {\n"\
"         memcpy(n_data + fir_cnt,data,sec_cnt*sizeof(%s));\n"\
"      }\n"\
"   }\n"\
"\n"\
,TYPE_NAME,TYPE_NAME);\
   if (TYPE_NUMBER & c_type_dynamic) {\
printf(\
"   if (size > used) {\n"\
"      %s *ptr;\n"\
"      %s *ptr_end;\n"\
"      %s *s_ptr;\n"\
"\n"\
"      if (begin + used >= size) {\n"\
"         ptr = data + (begin + used - size);\n"\
"         ptr_end = data + begin;\n"\
"         s_ptr = NULL;\n"\
"      }\n"\
"      else {\n"\
"         ptr = data;\n"\
"         ptr_end = data + begin;\n"\
"         s_ptr = ptr_end + used;\n"\
"      }\n"\
"\n"\
"      if (ptr < ptr_end) {\n"\
"         do {\n"\
"            ptr->clear();\n"\
"         } while(++ptr < ptr_end);\n"\
"      }\n"\
"\n"\
"      if (s_ptr != NULL) {\n"\
"         %s *s_ptr_end = data + size;\n"\
"         do {\n"\
"            s_ptr->clear();\n"\
"         } while(++s_ptr < s_ptr_end);\n"\
"      }\n"\
"   }\n"\
"\n"\
,TYPE_NAME,TYPE_NAME,TYPE_NAME,TYPE_NAME);\
   }\
printf(\
"   if (size != 0) {\n"\
"      cfree(data);\n"\
"   }\n"\
"\n"\
"   data = n_data;\n"\
"   size = a_size;\n"\
"   begin = 0;\n"\
"}/*}}}*/\n"\
"\n"\
);\
}

#define QUEUE_OPERATOR_EQUAL() \
{\
   if (!(TYPE_NUMBER & c_type_dynamic)) {\
printf(\
"inline %s &%s::operator=(%s &src)\n"\
,IM_STRUCT_NAME,IM_STRUCT_NAME,IM_STRUCT_NAME);\
   }\
   else {\
printf(\
"%s &%s::operator=(%s &src)\n"\
,IM_STRUCT_NAME,IM_STRUCT_NAME,IM_STRUCT_NAME);\
   }\
printf(\
"{/*{{{*/\n"\
"   clear();\n"\
"\n"\
"   if (src.used == 0) return *this;\n"\
"\n"\
"   copy_resize(src.used);\n"\
"\n"\
);\
   if (!(TYPE_NUMBER & c_type_dynamic)) {\
printf(\
"   unsigned fir_cnt;\n"\
"   unsigned sec_cnt;\n"\
"\n"\
"   if (src.begin + src.used > src.size) {\n"\
"      sec_cnt = src.begin + src.used - src.size;\n"\
"      fir_cnt = src.used - sec_cnt;\n"\
"   }\n"\
"   else {\n"\
"      fir_cnt = src.used;\n"\
"      sec_cnt = 0;\n"\
"   }\n"\
"\n"\
"   memcpy(data,src.data + src.begin,fir_cnt*sizeof(%s));\n"\
"\n"\
"   if (sec_cnt != 0) {\n"\
"      memcpy(data + fir_cnt,src.data,sec_cnt*sizeof(%s));\n"\
"   }\n"\
"\n"\
,TYPE_NAME,TYPE_NAME);\
   }\
   else {\
printf(\
"   unsigned sec_cnt;\n"\
"   %s *ptr = data;\n"\
"   %s *s_ptr = src.data + src.begin;\n"\
"   %s *s_ptr_end;\n"\
"\n"\
"   if (src.begin + src.used > src.size) {\n"\
"      s_ptr_end = src.data + src.size;\n"\
"      sec_cnt = src.begin + src.used - src.size;\n"\
"   }\n"\
"   else {\n"\
"      s_ptr_end = s_ptr + src.used;\n"\
"      sec_cnt = 0;\n"\
"   }\n"\
"\n"\
"   do {\n"\
"      *ptr = *s_ptr; \n"\
"   } while(++ptr,++s_ptr < s_ptr_end);\n"\
"\n"\
"   if (sec_cnt != 0) {\n"\
"      s_ptr = src.data;\n"\
"      s_ptr_end = s_ptr + sec_cnt;\n"\
"\n"\
"      do {\n"\
"         *ptr = *s_ptr;\n"\
"      } while(++ptr,++s_ptr < s_ptr_end);\n"\
"   }\n"\
"\n"\
,TYPE_NAME,TYPE_NAME,TYPE_NAME);\
   }\
printf(\
"   used = src.used;\n"\
"   return *this;\n"\
"}/*}}}*/\n"\
"\n"\
);\
}

#define QUEUE_OPERATOR_DOUBLE_EQUAL() \
{\
printf(\
"bool %s::operator==(%s &second)\n"\
"{/*{{{*/\n"\
"   if (used != second.used) return false;\n"\
"   if (used == 0) return true;\n"\
"\n"\
,IM_STRUCT_NAME,IM_STRUCT_NAME);\
   if (!(TYPE_NUMBER & c_type_dynamic)) {\
printf(\
"   bool _break;\n"\
"   bool s_break;\n"\
"   unsigned pos;\n"\
"   unsigned pos_end;\n"\
"   unsigned s_pos;\n"\
"\n"\
"   _break = (begin + used > size);\n"\
"   s_break = (second.begin + second.used > second.size);\n"\
"   pos = begin;\n"\
"   s_pos = second.begin;\n"\
"\n"\
"   if (_break) {\n"\
"      pos_end = begin + used - size;\n"\
"   }\n"\
"   else {\n"\
"      pos_end = begin + used;\n"\
"   }\n"\
"\n"\
"   do {\n"\
"      if (_break) {\n"\
"         unsigned offset = size - pos;\n"\
"         \n"\
"         if (s_break) {\n"\
"            unsigned s_offset = second.size = s_pos;\n"\
"\n"\
"            if (offset < s_offset) {\n"\
"               if (memcmp(data + pos,second.data + s_pos,offset*sizeof(%s)) != 0) {\n"\
"                  return false;\n"\
"               }\n"\
"\n"\
"               s_pos += offset;\n"\
"               pos = 0;\n"\
"               _break = false;\n"\
"            }\n"\
"            else {\n"\
"               if (memcmp(data + pos,second.data + s_pos,s_offset*sizeof(%s)) != 0) {\n"\
"                  return false;\n"\
"               }\n"\
"\n"\
"               if (pos += s_offset >= size) {\n"\
"                  pos = 0;\n"\
"                  _break = false;\n"\
"               }\n"\
"               s_pos = 0;\n"\
"               s_break = false;\n"\
"            }\n"\
"         }\n"\
"         else {\n"\
"            if (memcmp(data + pos,second.data + s_pos,offset*sizeof(%s)) != 0) {\n"\
"               return false;\n"\
"            }\n"\
"            s_pos += offset;\n"\
"            pos = 0;\n"\
"            _break = false;\n"\
"         }\n"\
"      }\n"\
"      else {\n"\
"         if (s_break) {\n"\
"            unsigned s_offset = second.size - s_pos;\n"\
"\n"\
"            if (memcmp(data + pos,second.data + s_pos,s_offset*sizeof(%s)) != 0) {\n"\
"               return false;\n"\
"            }\n"\
"            pos += s_offset;\n"\
"            s_pos = 0;\n"\
"            s_break = false;\n"\
"         }\n"\
"         else {\n"\
"            if (memcmp(data + pos,second.data + s_pos,(pos_end - pos)*sizeof(%s)) != 0) {\n"\
"               return false;\n"\
"            }\n"\
"            else {\n"\
"               return true;\n"\
"            }\n"\
"         }\n"\
"      }\n"\
"   } while(1);\n"\
,TYPE_NAME,TYPE_NAME,TYPE_NAME,TYPE_NAME,TYPE_NAME);\
   }\
   else {\
printf(\
"   %s *ptr = data + begin;\n"\
"   %s *ptr_break = data + size;\n"\
"   %s *ptr_end;\n"\
"   %s *s_ptr = second.data + second.begin;\n"\
"   %s *s_ptr_break = second.data + second.size;\n"\
"\n"\
"   if (begin + used > size) {\n"\
"      ptr_end = data + (begin + used - size);\n"\
"   }\n"\
"   else {\n"\
"      ptr_end = ptr + used;\n"\
"   }\n"\
"\n"\
"   do {\n"\
"      if (!(*ptr == *s_ptr)) {\n"\
"         return false;\n"\
"      }\n"\
"      \n"\
"      if (++ptr >= ptr_break) {\n"\
"         ptr = data;\n"\
"      }\n"\
"\n"\
"      if (++s_ptr >= s_ptr_break) {\n"\
"         s_ptr = second.data;\n"\
"      }\n"\
"\n"\
"   } while(ptr != ptr_end);\n"\
"\n"\
"   return true;\n"\
,TYPE_NAME,TYPE_NAME,TYPE_NAME,TYPE_NAME,TYPE_NAME);\
   }\
printf(\
"}/*}}}*/\n"\
"\n"\
);\
}

void processor_s::generate_queue_type()
{
   string_array_s &type_names = cont_params.types;
   string_array_s &fun_defs = cont_params.functions;
   string_array_s &abbs = cont_params.names;

   if (type_names.used != 1) {
      fprintf(stderr,"queue: not given name (or too many names) of contained type\n");
      cassert(0);
   }

   if (abbs.used < 1) {
      fprintf(stderr,"queue: not given name of generated structures\n");
      cassert(0);
   }

   unsigned type_abb_idx = abbreviations.get_idx_by_name(type_names[0].size - 1,type_names[0].data);
   if (type_abb_idx == c_idx_not_exist) {
      fprintf(stderr,"queue: contained type \"%s\" does not exist\n",type_names[0].data);
      cassert(0);
   }

   unsigned type_idx = abbreviations[type_abb_idx].data_type_idx;
   data_type_s &type = data_types[type_idx];

   // - test type options -
   if (type.properties & c_type_setting_strict_dynamic) {
      fprintf(stderr,"queue: container have not implemented processing of types with option strict_dynamic\n");
      cassert(0);
   }

   string_s real_name;
   real_name.init();
   real_name.conc_set(type.name.size - 1,type.name.data,strlen(c_cont_postfixes[c_cont_queue]),(char *)c_cont_postfixes[c_cont_queue]);

   string_s &data_type_name = abbs[0];

   unsigned data_type_idx;

   if ((data_type_idx = abbreviations.get_idx_by_name(data_type_name.size - 1,data_type_name.data)) == c_idx_not_exist) {

      unsigned d_idx = data_types.get_idx_by_real_name(real_name.size - 1,real_name.data);
      if (d_idx != c_idx_not_exist) {
         fprintf(stderr,"DUPLICATE STRUCTURES: %s <-> %s\n",data_type_name.data,data_types[d_idx].name.data);
      }

      data_types.push_blank();
      data_type_s &data_type = data_types.last();

      data_type.cont_idx = c_cont_queue;
      data_type.name.set(data_type_name.size - 1,data_type_name.data);
      data_type.real_name.swap(real_name);

      data_type.properties = c_type_dynamic | c_type_flushable  | (type_settings & c_type_setting_mask);
      data_type.types.push(abbreviations[type_abb_idx].name);

      data_type_idx = data_types.used - 1;
   }
   else {
      fprintf(stderr,"queue: name of generated structure \"%s\" already exist\n",data_type_name.data);
      cassert(0);
   }

   real_name.clear();

   // - check and write abbreviations -
   if (abbs.used != 0) {
      unsigned idx = 0;
      do {
         string_s &abb = abbs[idx];

         if (abbreviations.get_idx_by_name(abb.size - 1,abb.data) != c_idx_not_exist) {
            fprintf(stderr,"queue: abreaviated name \"%s\" for generated structure is already used\n",abb.data);
            cassert(0);
         }

         abbreviations.push_blank();
         abbreviations.last().set(abb,data_type_idx);
      } while(++idx < abbs.used);
   }

   data_type_s &data_type = data_types[data_type_idx];

   // - definition of structure queue -

printf(
"// struct %s definition\n"
"\n"
,STRUCT_NAME);

   if (abbs.used > 1) {
      unsigned idx = 1;
      do {
printf(
"typedef struct %s %s;\n"
,abbs[0].data,abbs[idx].data);
      } while(++idx < abbs.used);
printf(
"\n"
);
   }

printf(
"/*!\n"
" * \\brief __GEN queue of type %s\n"
" */\n"
"struct %s\n"
"{\n"
"   unsigned size; //!< actual size of allocated space (element count)\n"
"   unsigned used; //!< count of stored elements\n"
"   unsigned begin; //!< position of first element\n"
"   %s *data; //!< pointer to queue elements\n"
"\n"
,TYPE_NAME,STRUCT_NAME,TYPE_NAME);
   if (!(data_type.properties & c_type_setting_not_generate_init)) {
printf(
"   /*!\n"
"    * \\brief __GEN initialize queue\n"
"    */\n"
"   inline void init();\n"
"\n"
);
   }
printf(
"   /*!\n"
"    * \\brief __GEN initialize queue of requested size\n"
"    * \\param a_size - requested size of queue\n"
"    */\n"
"   inline void init_size(unsigned a_size);\n"
"\n"
);
   if (!(TYPE_NUMBER & c_type_dynamic)) {
      if (!(data_type.properties & c_type_setting_not_generate_clear)) {
printf(
"   /*!\n"
"    * \\brief __GEN release memory used by queue\n"
"    */\n"
"   inline void clear();\n"
"\n"
);
      }
   }
   else {
      if (!(data_type.properties & c_type_setting_not_generate_clear)) {
printf(
"   /*!\n"
"    * \\brief __GEN release memory used by queue\n"
"    */\n"
"   void clear();\n"
"\n"
);
      }
   }
printf(
"   /*!\n"
"    * \\brief __GEN flush queue memory usage\n"
"    */\n"
"   inline void flush();\n"
"\n"
);
   if (!(TYPE_NUMBER & c_type_flushable)) {
printf(
"   /*!\n"
"    * \\brief __GEN flush queue memory usage, recursive on elements\n"
"    */\n"
"   inline void flush_all();\n"
"\n"
);
   }
   else {
printf(
"   /*!\n"
"    * \\brief __GEN flush queue memory usage, recursive on elements\n"
"    */\n"
"   void flush_all();\n"
"\n"
);
   }
   if (!(data_type.properties & c_type_setting_not_generate_swap)) {
printf(
"   /*!\n"
"    * \\brief __GEN swap members of queue with another queue\n"
"    * \\param second - reference to another queue\n"
"    */\n"
"   inline void swap(%s &second);\n"
"\n"
,STRUCT_NAME);
   }
   if (TYPE_NUMBER & c_type_basic) {
printf(
"   /*!\n"
"    * \\brief __GEN insert element to end of queue\n"
"    * \\param a_value - value inserted to end of queue\n"
"    */\n"
"   inline void insert(%s a_value);\n"
"\n"
,TYPE_NAME);
   }
   else {
printf(
"   /*!\n"
"    * \\brief __GEN insert element to end of queue\n"
"    * \\param a_value - value inserted to end of queue\n"
"    */\n"
"   inline void insert(%s &a_value);\n"
"\n"
,TYPE_NAME);
   }
printf(
"   /*!\n"
"    * \\brief __GEN insert blank element to the end of queue\n"
"    */\n"
"   inline void insert_blank();\n"
"\n"
"   /*!\n"
"    * \\brief __GEN return value of next element in queue, and remove it\n"
"    * \\return reference to next element\n"
"    */\n"
"   inline %s &next();\n"
"\n"
"   /*!\n"
"    * \\brief __GEN return value of last element in queue\n"
"    * \\return reference to last element\n"
"    */\n"
"   inline %s &last();\n"
"\n"
"   /*!\n"
"    * \\brief __GEN change queue capacity\n"
"    * \\param a_size - requested queue capacity\n"
"    */\n"
"   void copy_resize(unsigned a_size);\n"
"\n"
,TYPE_NAME,TYPE_NAME);
   if (!(data_type.properties & c_type_setting_not_generate_operator_equal)) {
      if (!(TYPE_NUMBER & c_type_dynamic)) {
printf(
"   /*!\n"
"    * \\brief __GEN copy queue from another queue\n"
"    * \\param src - reference to another queue\n"
"    * \\return reference to this queue\n"
"    */\n"
"   inline %s &operator=(%s &src);\n"
"\n"
,STRUCT_NAME,STRUCT_NAME);
      }
      else {
printf(
"   /*!\n"
"    * \\brief __GEN copy queue from another queue\n"
"    * \\param src - reference to another queue\n"
"    * \\return reference to this queue\n"
"    */\n"
"   %s &operator=(%s &src);\n"
"\n"
,STRUCT_NAME,STRUCT_NAME);
      }
   }
printf(
"   /*!\n"
"    * \\brief __GEN compare queue with another queue\n"
"    * \\param second - reference to another queue\n"
"    * \\return result of comparision\n"
"    */\n"
"   bool operator==(%s &second);\n"
"\n"
,STRUCT_NAME);
   if (fun_defs.used != 0) {
      unsigned f_idx = 0;
      do {
printf(
"   %s\n"
,fun_defs[f_idx].data);
      } while(++f_idx < fun_defs.used);
   }
printf(
"};\n"
"\n"
);
};

void processor_s::generate_queue_inlines(unsigned abb_idx,unsigned a_dt_idx)
{
   data_type_s &data_type = data_types[a_dt_idx];
   
   string_s &type_abb_string = data_type.types[0];
   unsigned type_abb_idx = abbreviations.get_idx_by_name(type_abb_string.size - 1,type_abb_string.data);

   if (type_abb_idx == c_idx_not_exist) {
      fprintf(stderr,"queue: inlines: abbeviated type name \"%s\" does not exist\n",type_abb_string.data);
      cassert(0);
   }

   unsigned type_idx = abbreviations[type_abb_idx].data_type_idx;
   data_type_s &type = data_types[type_idx];

   // - definition of inline methods -

printf(
"// --- struct %s inline method definition ---\n"
"\n"
,IM_STRUCT_NAME);

   // - queue init method -
   if (!(data_type.properties & c_type_setting_not_generate_init)) {
QUEUE_INIT();
   }

   // - queue init_size method -
QUEUE_INIT_SIZE();

   // - queue clear method -
   if (!(TYPE_NUMBER & c_type_dynamic)) {
      if (!(data_type.properties & c_type_setting_not_generate_clear)) {
QUEUE_CLEAR();
      }
   }

   // - queue flush method -
QUEUE_FLUSH();

   // - queue flush_all method -
   if (!(TYPE_NUMBER & c_type_flushable)) {
QUEUE_FLUSH_ALL();
   }

   // - queue swap method -
   if (!(data_type.properties & c_type_setting_not_generate_swap)) {
QUEUE_SWAP();
   }

   // - queue insert method -
QUEUE_INSERT();

   // - queue insert_blank method -
QUEUE_INSERT_BLANK();

   // - queue next method -
QUEUE_NEXT();

   // - queue last method -
QUEUE_LAST();

   // - queue copy_resize method -

   // - queue operator= method -
   if (!(TYPE_NUMBER & c_type_dynamic)) {
      if (!(data_type.properties & c_type_setting_not_generate_operator_equal)) {
QUEUE_OPERATOR_EQUAL();
      }
   }

   // - queue operator== method -
}

void processor_s::generate_queue_methods(unsigned abb_idx,unsigned a_dt_idx)
{
   data_type_s &data_type = data_types[a_dt_idx];
   
   string_s &type_abb_string = data_type.types[0];
   unsigned type_abb_idx = abbreviations.get_idx_by_name(type_abb_string.size - 1,type_abb_string.data);

   if (type_abb_idx == c_idx_not_exist) {
      fprintf(stderr,"queue: methods: abreviated type name \"%s\" does not exist\n",type_abb_string.data);
      cassert(0);
   }

   unsigned type_idx = abbreviations[type_abb_idx].data_type_idx;
   data_type_s &type = data_types[type_idx];

   // - definition of methods -

printf(
"// --- struct %s method definition ---\n"
"\n"
,IM_STRUCT_NAME);

   // - queue init method -

   // - queue init_size method -

   // - queue clear method -
   if (TYPE_NUMBER & c_type_dynamic) {
      if (!(data_type.properties & c_type_setting_not_generate_clear)) {
QUEUE_CLEAR();
      }
   }

   // - queue flush method -

   // - queue flush_all method -
   if (TYPE_NUMBER & c_type_flushable) {
QUEUE_FLUSH_ALL();
   }

   // - queue swap method -

   // - queue insert method -

   // - queue insert_blank method -

   // - queue next method -

   // - queue last method -

   // - queue copy_resize method -
QUEUE_COPY_RESIZE();

   // - queue operator= method -
   if (TYPE_NUMBER & c_type_dynamic) {
      if (!(data_type.properties & c_type_setting_not_generate_operator_equal)) {
QUEUE_OPERATOR_EQUAL();
      }
   }

   // - queue operator== method -
QUEUE_OPERATOR_DOUBLE_EQUAL();
}


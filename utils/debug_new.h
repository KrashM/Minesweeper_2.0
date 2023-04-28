#pragma once

#include <cstdio>
#include <cstddef>
#include <std::string>
#include <vector>

class allocator{

public:
    static allocator &get_instance(){

        static allocator instance;
        return instance;

    }

    void *addEntry(std::size_t const size, std::string const &filename, std::string const &function, std::size_t const line){
        
        void *ptr = malloc(size);
        if(!ptr) throw std::bad_alloc{};

        info_list.emplace_back(ptr, filename, function, line, size);

        return ptr;

    }

    void freeEntry(void * const ptr){

        if(ptr == nullptr) return;

        ptr_info toRemoveNode;

        for(v_iter i = info_list.begin(); i != info_list.end(); ++i)
            if((*i).ptr == ptr){

                free((*i).ptr);
                info_list.erase(i);
                return;

            }

    }
    
    void printList(){

        for(std::size_t i = 0; i < info_list.size(); ++i)
            printf("%zu. Found leaked object at %#x (size %zu[bytes]) allocated in: %s:%s:%zu\n", 
                i + 1, info_list[i].ptr, info_list[i].size, info_list[i].fileName.c_str(), info_list[i].function.c_str(), info_list[i].line);

    }
    
    void checkMemoryLeaks(){

        if(info_list.empty()){

            printf("Memory is clean\n");
            return;

        }

        for(std::size_t i = 0; i < info_list.size(); ++i){

            printf("%zu. Found leaked object at %#x (size %zu[bytes]) allocated in: %s:%s:%zu\n", 
                i + 1, info_list[i].ptr, info_list[i].size, info_list[i].fileName.c_str(), info_list[i].function.c_str(), info_list[i].line);
            free(info_list[i].ptr);

        }

    }

private:
    allocator() = default;

private:
    struct ptr_info{

        void *ptr;
        std::string fileName;
        std::string function;
        std::size_t line, size;

        ptr_info(): ptr(nullptr), fileName(""), function(""), line(0), size(0){}
        ptr_info(void * const ptr, std::string const &fileName, std::string const &function, std::size_t const line, std::size_t const size):
            ptr(ptr), fileName(fileName), function(function), line(line), size(size){}

    };

private:
    typedef vector<ptr_info>::iterator v_iter;
    vector<ptr_info> info_list;

};

inline void *operator new(std::size_t const size, bool, std::string const &fileName = __builtin_FILE(), std::string const &function = __builtin_FUNCTION(), std::size_t const line = __builtin_LINE()){ return allocator::get_instance().addEntry(size, fileName, function, line); }
inline void *operator new[](std::size_t const size, bool, std::string const &fileName = __builtin_FILE(), std::string const &function = __builtin_FUNCTION(), std::size_t const line = __builtin_LINE()){ return allocator::get_instance().addEntry(size, fileName, function, line); }

inline void operator delete(void *pointer) noexcept{ allocator::get_instance().freeEntry(pointer); }
inline void operator delete[](void *pointer) noexcept{ allocator::get_instance().freeEntry(pointer); }
inline void operator delete(void *pointer, std::size_t size) noexcept{ allocator::get_instance().freeEntry(pointer); }
inline void operator delete[](void *pointer, std::size_t size) noexcept{ allocator::get_instance().freeEntry(pointer); }
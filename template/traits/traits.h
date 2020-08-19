#ifndef MY_TRAITS_H
#define MY_TRAITS_H

namespace Train {
namespace Traits {
// remove_cv
template<typename T> struct remove_cv                    {  typedef T type;   };
template<typename T> struct remove_cv<const T>           {  typedef T type;   };
template<typename T> struct remove_cv<const volatile T>  {  typedef T type;   };
template<typename T> struct remove_cv<volatile T>        {  typedef T type;   };


// is_floating_point
template<class T> struct is_floating_point_cv               {  static const bool value = false; };
template<>        struct is_floating_point_cv<float>        {  static const bool value = true; };
template<>        struct is_floating_point_cv<double>       {  static const bool value = true; };
template<>        struct is_floating_point_cv<long double>  {  static const bool value = true; };

template<class T>
struct is_floating_point
   : is_floating_point_cv<typename remove_cv<T>::type>
{};

// is_integral
template<class T> struct is_integral_cv                    {  static const bool value = false; };
template<> struct is_integral_cv<                     bool>{  static const bool value = true; };
template<> struct is_integral_cv<                     char>{  static const bool value = true; };
template<> struct is_integral_cv<            unsigned char>{  static const bool value = true; };
template<> struct is_integral_cv<              signed char>{  static const bool value = true; };
template<> struct is_integral_cv<                 char16_t>{  static const bool value = true; };
template<> struct is_integral_cv<                 char32_t>{  static const bool value = true; };
template<> struct is_integral_cv<                  wchar_t>{  static const bool value = true; };
template<> struct is_integral_cv<                    short>{  static const bool value = true; };
template<> struct is_integral_cv<           unsigned short>{  static const bool value = true; };
template<> struct is_integral_cv<                      int>{  static const bool value = true; };
template<> struct is_integral_cv<             unsigned int>{  static const bool value = true; };
template<> struct is_integral_cv<                     long>{  static const bool value = true; };
template<> struct is_integral_cv<            unsigned long>{  static const bool value = true; };

template<class T>
struct is_integral
   : public is_integral_cv<typename remove_cv<T>::type>
{};


// is_void
template<class T>
struct is_void_cv
{  static const bool value = false; };

template<>
struct is_void_cv<void>
{  static const bool value = true; };

template<class T>
struct is_void
   : is_void_cv<typename remove_cv<T>::type>
{};


// is_array
template<class T>
struct is_array
{  static const bool value = false; };

template<class T>
struct is_array<T[]>
{  static const bool value = true;  };

template<class T, std::size_t N>
struct is_array<T[N]>
{  static const bool value = true;  };

// is_member_pointer
template <class T>         struct is_member_pointer_cv         {  static const bool value = false; };
template <class T, class U>struct is_member_pointer_cv<T U::*> {  static const bool value = true; };

template <class T>
struct is_member_pointer
    : is_member_pointer_cv<typename remove_cv<T>::type>
{};

// is_nullptr_t
template <class T> struct is_nullptr_t_cv
{  static const bool value = false; };

template <> struct is_nullptr_t_cv<decltype(nullptr)>
{  static const bool value = true; };


template <class T>
struct is_nullptr_t
   : is_nullptr_t_cv<typename remove_cv<T>::type>
{};

// remove_const
template<class T>
struct remove_const
{  typedef T type;   };

template<class T>
struct remove_const< const T>
{  typedef T type;   };

// add_reference
template<class T> struct add_lvalue_reference                     {  typedef T& type;  };
template<class T> struct add_lvalue_reference<T&>                 {  typedef T& type;  };
template<>        struct add_lvalue_reference<void>               {  typedef void type;   };
template<>        struct add_lvalue_reference<const void>         {  typedef const void type;  };
template<>        struct add_lvalue_reference<volatile void>      {  typedef volatile void type;   };
template<>        struct add_lvalue_reference<const volatile void>{  typedef const volatile void type;   };

template <typename T>
struct add_reference : add_lvalue_reference<T>
{};



template<class T, class U>
struct is_same
{
   static const bool value = false;
};
 
template<class T>
struct is_same<T, T>
{
   static const bool value = true;
};

}
}

#endif

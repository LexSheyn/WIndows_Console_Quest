#pragma once

#if _DEBUG
#define WCE_INLINE 
#else
#define WCE_INLINE inline
#endif

#define WCE_CALL __fastcall

#define WCE_NO_COPY(Class) Class(const Class&) = delete;\
                           Class& operator = (const Class&) = delete

#define WCE_NO_MOVE(Class) Class(Class&&) = delete;\
                           Class& operator = (Class&&) = delete

#define WCE_DEFAULT_COPY(Class) Class(const Class&) noexcept = default;\
                                Class& operator = (const Class&) = default

#define WCE_DEFAULT_MOVE(Class) Class(Class&&) noexcept = default;\
                                Class& operator = (Class&&) = default
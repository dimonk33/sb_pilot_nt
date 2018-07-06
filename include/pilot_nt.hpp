/**                                   5
 * @file public/pilot_nt.h
 * @author A. Brik, S. Papazov
 * @date 12 June 2016
 * @brief Public API for pilot_nt.dll.
 */
#ifndef _PILOT_NT_H_
#define _PILOT_NT_H_

#include <windows.h>

#ifdef UPOS
  #include "global.h"
  #include "public/paramsln.hpp"
  #define PILOT_NT_API __declspec(dllexport)
#else
  #include "paramsln.hpp"
  #define PILOT_NT_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C"{
#endif

#pragma pack(1)

/** ������������� ��������� �������� */
typedef long CONTEXT_PTR;

/** �������������� ����������, ������� ����� �������� ��� �������� ����� �������� �������� */
typedef enum {
PAR_LLT_ID          = 1,    ///< [out] ����� ��������� ���������� � ������� ������ �����, �����. �������� ������������ ��� ������ ������� ::card_authorize15 � ::ReadCardContext
PAR_PAN             = 2,    ///< [out] ������������� ����� �����, ������. �������� ������������ ��� ������ ������� ::ReadCardContext
PAR_HASH            = 3,    ///< [out] ���. ������. �������� ������������ �������� ::ReadCardContext
PAR_CARD_TYPE       = 4,    ///< [out] ��� �����. �����. �������� ������������ �������� ::ReadCardContext
PAR_OWN_CARD        = 5     ///< [out] ������� "����� �������� ����������". �����. �������� ������������ �������� ::ReadCardContext
} EParameterName;



/**
 * @defgroup FINANCIAL ���������� ��������
 */
/**@{*/

/** ���� �������� */
typedef enum {
OP_PURCHASE     = 1,   ///< ������ �������
OP_CASH         = 2,   ///< ������ �������� (������ ���)
OP_RETURN       = 3,   ///< ������� ���� ������ �������
OP_BALANCE      = 4,   ///< ������ (������ ���)
OP_FUNDS        = 6,   ///< ������.������� (������ ���)
OP_ADD_AUTH     = 42,  ///< ���������� ���������������
OP_CANC_AUTH    = 43,  ///< ������ ���������������
OP_PREAUTH      = 51,  ///< ���������������
OP_COMPLETION   = 52,  ///< ���������� �������
OP_CASHIN       = 53,  ///< ����� �������� (������ ���)
OP_CASHIN_COMP  = 54,  ///< ������������� ������ (������ ���)
OP_PILOT_START  = 55,  ///< ������ ������ � �������� (������ ���)
OP_PILOT_STATUS = 56,  ///< ����� ������� ����� ������� (������ ���)
OP_PILOT_STOP   = 57,  ///< ��������� ������ � �������� (������ ���)
OP_SETPIN       = 58,  ///< ��������� ���� (������ ���)
OP_CHANGEPIN    = 59,  ///< ����� ���� (������ ���)
} OpetationTypes;

/**
 * �������� ��������� ��������
 * ���������, ������������ ��� �������� �������� � ��������� ����������� ���������� ��������.
 */
struct auth_answer{
   int TType;             /**< [in] ��� ����������. �� ::OpetationTypes */
   unsigned long Amount;  /**< [in] ����� � ��������                    */
   char RCode[3];         /**< [out] ��� ���������� �����������         */
   char AMessage[16];     /**< [out] ����� ���������� �����������       */
   int  CType;            /**< [in,out] ��� �����                       */
   char* Check;           /**< [out] ����� ����, ������ ������������� GlobalFree � ���������� ��������� */
};

/** @brief ���������� �������� �� ������
 *  @param[in] track2 ������ ������� ����� � ��������� �������. ���� NULL, �� ����� ���������� ������� �����.
 *  @param[in,out] auth_answer �������� ��������� ��������. ��. ::auth_answer
 *  @return int ��� ������.
 */
PILOT_NT_API int card_authorize(char *track2, struct auth_answer *auth_answer);

/** @struct auth_answer2
 *  @brief ���������� ��� ��������� ���� ����������� �������� ��������.
 */
struct auth_answer2{
  struct auth_answer auth_answ;  /**< [in]  �������� ��������� ��������. ��. ::auth_answer */
  char AuthCode[MAX_AUTHCODE];  /**< [out] ��� �����������. 7 ����.              */
};

/** @brief ���������� �������� �� ������
 *  @param[out] track2 - ������ ������� ����� � ��������� �������. ���� NULL, �� ����� ���������� ������� �����.
 *  @param[in,out] auth_answer - ��. ::auth_answer2
 *  @return int ��� ������.
 */
PILOT_NT_API int  card_authorize2(char *track2, struct auth_answer2 *auth_answer);

/** @struct auth_answer3
 *  @brief ���������� ��� ��������� ���� ����������� �������� �������� � ������ �����.
 */
struct auth_answer3{
  struct auth_answer auth_answ; /**< [in, out]  �������� ��������� ��������. ��. ::auth_answer */
  char AuthCode[MAX_AUTHCODE]; /**< [out] ��� �����������. 7 ����.                       */
  char CardID[CARD_ID_LEN];     /**< [out] ������������� �����. 25 ����. ��� ������������� ���� ��� �������, ����� ������ 6 � ��������� 4, ����� �������� ��������� �*�.*/
};

/** @brief ���������� �������� �� ������
 *  @param[in] track2 ������ ������� ����� � ��������� �������. ���� NULL, �� ����� ���������� ������� �����.
 *  @param[in,out] auth_answer ��. ::auth_answer3
 *  @return int ��� ������.
 */
PILOT_NT_API int  card_authorize3(char *track2, struct auth_answer3 *auth_answer);

/** @struct auth_answer4
 *  @brief ���������� ��� ��������� ���� ����������� �������� ��������, ������ �����, ���� ������, ������� �������� � ������ �������� �� �����.
 */
struct auth_answer4{
  struct auth_answer auth_answ; /**< [in, out]  �������� ��������� ��������. ��. ::auth_answer */
  char AuthCode[MAX_AUTHCODE]; /**< [out] ��� �����������. 7 ����.                            */
  char CardID[CARD_ID_LEN];     /**< [out] ������������� �����. 25 ����.                       */
  int  ErrorCode;               /**< [out] ��� ������.                                         */
  char TransDate[TRANSDATE_LEN];/**< [out] ���� � ����� ��������                               */
  int  TransNumber;             /**< [out] ����� �������� �� ����. ����, ��. ����� �� ����     */
};

/** @brief ���������� �������� �� ������
 *  @param[in] track2 ������ ������� ����� � ��������� �������. ���� NULL, �� ����� ���������� ������� �����.
 *  @param[in,out] auth_answer ��. ::auth_answer4
 *  @return int ��� ������.
 */
PILOT_NT_API int  card_authorize4(char *track2, struct auth_answer4 *auth_answer);

/** @struct auth_answer5
 *  @brief ���������� ��� ��������� ���� ����������� �������� �������� � ������ ������ (RRN).
 */
struct auth_answer5{
  struct auth_answer auth_answ;   /**< [in]  �������� ��������� ��������. ��. ::auth_answer */
  char   RRN[MAX_REFNUM];         /**< [in,out] ����� ������ ��������, ����������� ������. ������������
                                                ��� �������� ������� � ������������� �����������.
                                                �������� ���������� 12-������� ��������� �����.
                                                ��� ��������������� ��� ���� �������� ��������
                                                (��� ��������� ���������� pilot_nt.dll), � ���
                                                ���������� ������� � ������� (�������� ������ 
                                                ���� ��������� ���������� ����������; ��� ������
                                                ��������� �� ���������, ������������ ��� ���������������).*/
  char   AuthCode[MAX_AUTHCODE]; /**< [out] ��� �����������. 7 ����.                       */
};

/** @brief ���������� �������� �� ������
 *  @param[out] track2 - ������ ������� ����� � ��������� �������. ���� NULL, �� ����� ���������� ������� �����.
 *  @param[in,out] auth_answer - ��. ::auth_answer5
 *  @return int ��� ������.
 */
PILOT_NT_API int  card_authorize5(char *track2, struct auth_answer5 *auth_answer);

/** @struct auth_answer6
 *  @brief ���������� ��� ��������� ������ ��� ��� ���������� auth_answer5 � auth_answer4.
 */
struct auth_answer6{
  struct auth_answer auth_answ;    /**< [in, out]  �������� ��������� ��������. ��. ::auth_answer  */
  char   AuthCode[MAX_AUTHCODE];  /**< [out] ��� �����������. 7 ����.                             */
  char   CardID[CARD_ID_LEN];      /**< [out] ������������� �����. 25 ����.                        */
  int    ErrorCode;                /**< [out] ��� ������.                                          */
  char   TransDate[TRANSDATE_LEN]; /**< [out] ���� � ����� ��������                                */
  int    TransNumber;              /**< [out] ����� �������� �� ����. ����, ��. ����� �� ����      */
  char   RRN[MAX_REFNUM];          /**< [in,out] ����� ������ ��������, ����������� ������. ������������
                                                ��� �������� ������� � ������������� �����������.
                                                �������� ���������� 12-������� ��������� �����.
                                                ��� ��������������� ��� ���� �������� ��������
                                                (��� ��������� ���������� pilot_nt.dll), � ���
                                                ���������� ������� � ������� (�������� ������ 
                                                ���� ��������� ���������� ����������; ��� ������
                                                ��������� �� ���������, ������������ ��� ���������������).*/
};

/** @brief ���������� �������� �� ������
 *  @param[in] track2 ������ ������� ����� � ��������� �������. ���� NULL, �� ����� ���������� ������� �����.
 *  @param[in,out] auth_answer ��. ::auth_answer6
 *  @return int ��� ������.
 */
PILOT_NT_API int  card_authorize6(char *track2, struct auth_answer6 *auth_answer);

/** @struct payment_info_item
 *  @brief ������� ������� ����� ��� �������� �� ������ ��������� �������
 */
struct payment_info_item{
  DWORD  dwTag;                   /**< ��� ��������� �������. */
  char   Value[MAX_PAYMENT_ITEM]; /**< �������� ���� ��������� �������. 128 ����. ::MAX_PAYMENT_ITEM */
  BYTE   Flags;                   /**< must be 0x40 for immediate sending */
  void*  pNextItem;               /**< ��������� ������� �������. � ������ NULL, ��� ��������� ������� �������. */
};

/** @brief ���������� �������� �� ������
 *  @param[in] track2 ������ ������� ����� � ��������� �������. ���� NULL, �� ����� ���������� ������� �����.
 *  @param[in,out] auth_answer ��. ::auth_answer6
 *  @param[in,out] payinfo ��. ::payment_info_item
 *  @return int ��� ������.
 */
PILOT_NT_API int  card_authorize6_ext(
  char *track2,
  struct auth_answer6 *auth_answer,
  struct payment_info_item *payinfo
);

/** @struct auth_answer7
 *  @brief ���������� ��� ��������� ���� ����������� �������� ��������, ������ ����� � �������� �������������� ����� ���������.
 */
struct auth_answer7{
  struct auth_answer auth_answ;    /**< [in, out]  �������� ��������� ��������. ��. ::auth_answer */
  char   AuthCode[MAX_AUTHCODE];  /**< [out] ��� �����������. 7 ����.                            */
  char   CardID [CARD_ID_LEN];     /**< [out] ������������� �����. 25 ����.                       */
  int    SberOwnCard;              /**< [out] ���� �������������� ����� ���������                 */
};

/** @brief ���������� �������� �� ������
 *  @param[in] track2 ������ ������� ����� � ��������� �������. ���� NULL, �� ����� ���������� ������� �����.
 *  @param[in,out] auth_answer ��. ::auth_answer7
 *  @return int ��� ������.
 */
PILOT_NT_API int  card_authorize7(char *track2, struct auth_answer7 *auth_answer);


/** @struct auth_answer8
 *  @brief ���������� ��� ��������� ������ ��� ��� ���������� auth_answer5 � auth_answer4, � ����� ������ ����� � ����� �������� � ����������� ����.
 */
struct auth_answer8{
  struct auth_answer auth_answ;      /**< [in, out]  �������� ��������� ��������. ��. ::auth_answer */
  char   AuthCode[MAX_AUTHCODE];    /**< [out] ��� �����������. 7 ����.                            */
  char   CardID[CARD_ID_LEN];        /**< [out] ������������� �����. 25 ����.                       */
  int    ErrorCode;                  /**< [out] ��� ������.                                         */
  char   TransDate[TRANSDATE_LEN];   /**< [out] ���� � ����� ��������                               */
  int    TransNumber;                /**< [out] ����� �������� �� ����. ����, ��. ����� �� ����     */
  char   RRN[MAX_REFNUM];            /**< [in,out] ����� ������ ��������, ����������� ������. ������������
                                                ��� �������� ������� � ������������� �����������.
                                                �������� ���������� 12-������� ��������� �����.
                                                ��� ��������������� ��� ���� �������� ��������
                                                (��� ��������� ���������� pilot_nt.dll), � ���
                                                ���������� ������� � ������� (�������� ������ 
                                                ���� ��������� ���������� ����������; ��� ������
                                                ��������� �� ���������, ������������ ��� ���������������).*/
  char   EncryptedData[MAX_ENCR_DATA*2+1]; /**< [in, out] ����������� ����� ����� � ���� ��������. �� ���������� ��� ��������� ���.   */
};
/** @brief ���������� �������� �� ������
 *  @note ������� ��������� ���������� ������������� �����. ��� ������ �� ��������� ��� ���� EncryptedData �� �����������.
 *  @param[in] track2 ������ ������� ����� � ��������� �������. ���� NULL, �� ����� ���������� ������� �����.
 *  @param[in,out] auth_answer ��. ::auth_answer8
 *  @return int ��� ������.
 */
PILOT_NT_API int  card_authorize8(char *track2, struct auth_answer8 *auth_answer);

/** @struct preauth_rec
 *  @brief  ��������� ��� �������� ����� �������� � ������, �� ������� ����� ��������� ���������� �������.
 */
struct preauth_rec{
  unsigned long  Amount;          /**< [in] ����� � ��������              */
  char   RRN[MAX_REFNUM];         /**< [in,out] ����� ������ ��������, ����������� ������. ������������
                                                ��� �������� ������� � ������������� �����������.
                                                �������� ���������� 12-������� ��������� �����.
                                                ��� ��������������� ��� ���� �������� ��������
                                                (��� ��������� ���������� pilot_nt.dll), � ���
                                                ���������� ������� � ������� (�������� ������
                                                ���� ��������� ���������� ����������; ��� ������
                                                ��������� �� ���������, ������������ ��� ���������������).*/
  char           Last4Digits[5];  /**< [in] ��������� 4 ����� ������ �����*/
  unsigned short ErrorCode;       /**< [out] ��� ������.                  */
};

/** @brief ���������� �������� �� ������
 *  @param[in] track2 ������ ������� ����� � ��������� �������. ���� NULL, �� ����� ���������� ������� �����.
 *  @param[in,out] auth_ans ��. ::auth_answer8
 *  @param[in,out] pPreAuthList ������ �������� � ���������, �� ������� ��������� ��������� "���������� �������". ��. ::preauth_rec
 *  @param[in] NumAuths ����� ���������� ��������, �� ������� ��������� ��������� "���������� �������".
 *  @return int ��� ������.
 */
PILOT_NT_API int card_complete_multi_auth8(
  char* track2,
  struct auth_answer8* auth_ans,
  struct preauth_rec*  pPreAuthList,
  int NumAuths
);

/** @struct auth_answer9
*  @brief ���������� ��� ��������� ���� ����������� �������� ��������, ������ �����, ���� ������ ����� � �������� �������������� ����� ���������.
 */
struct auth_answer9{
  auth_answer   ans;                     /**< [in, out]  �������� ��������� ��������. ��. ::auth_answer */
  char          AuthCode[MAX_AUTHCODE]; /**< [out] ��� �����������. 7 ����.                            */
  char          CardID [CARD_ID_LEN];    /**< [out] ������������� �����. 25 ����.                       */
  int           SberOwnCard;             /**< [out] ���� �������������� ����� ���������                 */
  char          Hash[CARD_HASH_LEN];     /**< [in, out] ��� SHA1 �� ������ �����, � ������� ASCII � ������� ������ � �����. 40 ����.*/
};

/** @brief ���������� �������� �� ������
 *  @param[in] track2 ������ ������� ����� � ��������� �������. ���� NULL, �� ����� ���������� ������� �����.
 *  @param[in,out] auth_answer ��. ::auth_answer9
 *  @return int ��� ������.
 */
PILOT_NT_API int  card_authorize9(char *track2, struct auth_answer9 *auth_answer);

/** @struct auth_answer10
 *  @brief ���������� ��� ��������� ������ ��� ��� ���������� auth_answer4, � ����� �������������� ����� ���������
 *  � ���� �� ������ �����.
 */
struct auth_answer10{
  auth_answer   ans;               /**< [in, out]  �������� ��������� ��������. ��. ::auth_answer */
  char   AuthCode[MAX_AUTHCODE];  /**< [out] ��� �����������. 7 ����.              */
  char   CardID[CARD_ID_LEN];      /**< [out] ������������� �����. 25 ����. ��� ������������� ���� ��� �������, ����� ������ 6 � ��������� 4, ����� �������� ��������� �*�.*/
  int    ErrorCode;                /**< [out] ��� ������.                                         */
  char   TransDate[TRANSDATE_LEN]; /**< [out] ���� � ����� ��������                               */
  int    TransNumber;              /**< [out] ����� �������� �� ����. ����, ��. ����� �� ����     */
  int    SberOwnCard;              /**< [out] ���� �������������� ����� ���������                 */
  char   Hash[CARD_HASH_LEN];      /**< [in, out] ��� �� ������ �����, � ������� ASCII � ������� ������ � �����*/
};

/** @brief ���������� �������� �� ������
 *  @param[in] track2 ������ ������� ����� � ��������� �������. ���� NULL, �� ����� ���������� ������� �����.
 *  @param[in,out] auth_answer ��. ::auth_answer10
 *  @return int ��� ������.
 */
PILOT_NT_API int  card_authorize10(char *track2, struct auth_answer10 *auth_answer);

/** @struct auth_answer11
 *  @brief ���������� ��� ��������� ���� ����������� �������� ��������, ������ �����, ���� ������,
 *         ����, ������� � ������ ��������, ���� ������ �����, �������� �������������� ����� ���������, ������� ������� �����.
 
 */
struct auth_answer11{
  auth_answer   ans;               /**< [in, out]  �������� ��������� ��������. ��. ::auth_answer */
  char   AuthCode[MAX_AUTHCODE];  /**< [out] ��� �����������. 7 ����.              */
  char   CardID[CARD_ID_LEN];      /**< [out] ������������� �����. 25 ����. ��� ������������� ���� ��� �������, ����� ������ 6 � ��������� 4, ����� �������� ��������� �*�.*/
  int    ErrorCode;                /**< [out] ��� ������.                                         */
  char   TransDate[TRANSDATE_LEN]; /**< [out] ���� � ����� ��������                               */
  int    TransNumber;              /**< [out] ����� �������� �� ����. ����, ��. ����� �� ����     */
  int    SberOwnCard;              /**< [out] ���� �������������� ����� ���������                 */
  char   Hash[CARD_HASH_LEN];      /**< [in, out] ��� SHA1 �� ������ �����, � ������� ASCII � ������� ������ � �����. 40 ����.*/
  char   Track3[CARD_TRACK3_LEN];  /**< [out] ������ ������� �����*/
  unsigned long RequestID;         /**< [in,out] ���������� ����� ��������. ������ PCI DSS �������.*/
};

/** @brief ���������� �������� �� ������
 *  @param[in] track2 ������ ������� ����� � ��������� �������. ���� NULL, �� ����� ���������� ������� �����.
 *  @param[in,out] auth_answer ��. ::auth_answer11
 *  @return int ��� ������.
 */
PILOT_NT_API int  card_authorize11(char *track2, struct auth_answer11 *auth_answer);

/** @struct auth_answer12
 *  @brief ���������� card_authorize11 ������������ ������� ����� ������ � ������/�������� ����� ������.
 */
struct auth_answer12 {
  auth_answer   ans;              /**< [in, out]  �������� ��������� ��������. ��. ::auth_answer */
  char   AuthCode[MAX_AUTHCODE]; /**< [out] ��� �����������. 7 ����.              */
  char   CardID[CARD_ID_LEN];     /**< [out] ������������� �����. 25 ����. ��� ������������� ���� ��� �������, ����� ������ 6 � ��������� 4, ����� �������� ��������� �*�.*/
  int    ErrorCode;               /**< [out] ��� ������.                                         */
  char   TransDate[TRANSDATE_LEN];/**< [out] ���� � ����� ��������                               */
  int    TransNumber;             /**< [out] ����� �������� �� ����. ����, ��. ����� �� ����     */
  int    SberOwnCard;             /**< [out] ���� �������������� ����� ���������                 */
  char   Hash[CARD_HASH_LEN];     /**< [in, out] ��� SHA1 �� ������ �����, � ������� ASCII � ������� ������ � �����. 40 ����.*/
  char   Track3[CARD_TRACK3_LEN]; /**< [out] ������ ������� �����*/
  unsigned long RequestID;        /**< [in,out] ���������� ����� ��������. ������ PCI DSS �������.*/
  DWORD  Department;              /**< [in] ���������� ����� ������ �� 0 �� 14-��, ������������.
                                            ��� ��������� ������ ������ � 0xFFFFFFFF, ����� ������
                                            ����� �������� ����� ��������� ��������� ����� ������� �����.
                                            ���� ����� ������ ����� ������ ��� ������������ ���������,
                                            �� �������� ������ ��� ������ 4191. */
  char   RRN[MAX_REFNUM];         /**< [in,out] ����� ������ ��������, ����������� ������. ������������
                                                ��� �������� ������� � ������������� �����������.
                                                �������� ���������� 12-������� ��������� �����.
                                                ��� ��������������� ��� ���� �������� ��������
                                                (��� ��������� ���������� pilot_nt.dll), � ���
                                                ���������� ������� � ������� (�������� ������ 
                                                ���� ��������� ���������� ����������; ��� ������
                                                ��������� �� ���������, ������������ ��� ���������������).*/
};

/** @brief ���������� �������� �� ������
 *  @param[in] track2 ������ ������� ����� � ��������� �������. ���� NULL, �� ����� ���������� ������� �����.
 *  @param[in,out] auth_answer ��. ::auth_answer12
 *  @return int ��� ������.
 */
PILOT_NT_API int  card_authorize12(char *track2, struct auth_answer12 *auth_answer);

/** @struct auth_answer13
 *  @brief ���������� card_authorize11 ������������ ������� ����� ������, ��� ������ � �������� ������ ������ �����, ��� ������� ����� � AID.
 */
struct auth_answer13{

  auth_answer   ans;              /**< [in, out]  �������� ��������� ��������. ��. ::auth_answer */
  char   AuthCode[MAX_AUTHCODE]; /**< [out] ��� �����������. 7 ����.                       */
  char   CardID[CARD_ID_LEN];     /**< [out] ������������� �����. 25 ����. ��� ������������� ���� ��� �������, ����� ������ 6 � ��������� 4, ����� �������� ��������� �*�.*/
  int    ErrorCode;               /**< [out] ��� ������.                                         */
  char   TransDate[TRANSDATE_LEN];/**< [out] ���� � ����� ��������                               */
  int    TransNumber;             /**< [out] ����� �������� �� ����. ����, ��. ����� �� ����     */
  int    SberOwnCard;             /**< [out] ���� �������������� ����� ���������                 */
  char   Hash[CARD_HASH_LEN];     /**< [in, out] ��� SHA1 �� ������ �����, � ������� ASCII � ������� ������ � �����. 40 ����.*/
  char   Track3[CARD_TRACK3_LEN]; /**< [out] ������ ������� �����*/
  DWORD  RequestID;               /**< [in,out] ���������� ����� ��������. ������ PCI DSS �������.*/
  DWORD  Department;              /**< [in] ���������� ����� ������ �� 0 �� 14-��, ������������.
                                            ��� ��������� ������ ������ � 0xFFFFFFFF, ����� ������
                                            ����� �������� ����� ��������� ��������� ����� ������� �����.
                                            ���� ����� ������ ����� ������ ��� ������������ ���������,
                                            �� �������� ������ ��� ������ 4191. */
  char   RRN[MAX_REFNUM];         /**< [in,out] ����� ������ ��������, ����������� ������. ������������
                                                ��� �������� ������� � ������������� �����������.
                                                �������� ���������� 12-������� ��������� �����.
                                                ��� ��������������� ��� ���� �������� ��������
                                                (��� ��������� ���������� pilot_nt.dll), � ���
                                                ���������� ������� � ������� (�������� ������
                                                ���� ��������� ���������� ����������; ��� ������
                                                ��������� �� ���������, ������������ ��� ���������������).*/
  DWORD  CurrencyCode;            /**< [in] ������������� ��� ������ (810, 643, 840, 978 � �.�.) */
  char   CardEntryMode;           /**< [out] ������ ������ ����� ('D'-����.������, 'M'-������ ����, 'C'-���, 'E'-���������� EMV, 'R'-���������� magstripe, 'F'-fallback)*/
  char   CardName[MAX_CARD_NAME_LEN]; /**< [out] �������� ���� ����� */
  char   AID[MAX_AID_ASCII_LEN];  /**< [out] Application ID ������� ����� (� ���� ASCIIZ-������)*/
  char   FullErrorText[MAX_FULL_ERROR_TEXT]; /**< [out] ������ ����� ��������� �� ������*/
};

/** @brief ���������� �������� �� ������
 *  @param[in] track2 ������ ������� ����� � ��������� �������. ���� NULL, �� ����� ���������� ������� �����.
 *  @param[in,out] auth_answer ��. ::auth_answer13
 *  @return int ��� ������.
 */
PILOT_NT_API int  card_authorize13(char *track2, struct auth_answer13 *auth_answer);

/** @struct auth_answer14
 *  @brief ���������� card_authorize13 ������������ ������� ���������� � ������.
 */
struct auth_answer14 {
  auth_answer   ans;               /**< [in, out]  �������� ��������� ��������. ��. ::auth_answer */
  char   AuthCode[MAX_AUTHCODE];  /**< [out] ��� �����������. 7 ����.              */
  char   CardID[CARD_ID_LEN];      /**< [out] ������������� �����. 25 ����. ��� ������������� ���� ��� �������, ����� ������ 6 � ��������� 4, ����� �������� ��������� �*�.*/
  int    ErrorCode;                /**< [out] ��� ������.                                         */
  char   TransDate[TRANSDATE_LEN]; /**< [out] ���� � ����� ��������                               */
  int    TransNumber;              /**< [out] ����� �������� �� ����. ����, ��. ����� �� ����     */
  int    SberOwnCard;              /**< [out] ���� �������������� ����� ���������                 */
  char   Hash[CARD_HASH_LEN];      /**< [in, out] ��� SHA1 �� ������ �����, � ������� ASCII � ������� ������ � �����. 40 ����.*/
  char   Track3[CARD_TRACK3_LEN];  /**< [out] ������ ������� �����*/
  DWORD  RequestID;                /**< [in,out] ���������� ����� ��������. ������ PCI DSS �������.*/
  DWORD  Department;              /**< [in] ���������� ����� ������ �� 0 �� 14-��, ������������.
                                            ��� ��������� ������ ������ � 0xFFFFFFFF, ����� ������
                                            ����� �������� ����� ��������� ��������� ����� ������� �����.
                                            ���� ����� ������ ����� ������ ��� ������������ ���������,
                                            �� �������� ������ ��� ������ 4191. */
  char   RRN[MAX_REFNUM];          /**< [in,out] ����� ������ ��������, ����������� ������. ������������
                                                ��� �������� �������, ������������� ����������� � ���������� �������.
                                                �������� ���������� 12-������� ��������� �����.
                                                ��� ��������������� ��� ���� �������� ��������
                                                (��� ��������� ���������� pilot_nt.dll), � ���
                                                ���������� ������� � ������� (�������� ������ 
                                                ���� ��������� ���������� ����������; ��� ������
                                                ��������� �� ���������, ������������ ��� ���������������).*/
  DWORD  CurrencyCode;             /**< [in] ������������� ��� ������ (810, 643, 840, 978 � �.�.) */
  char   CardEntryMode;            /**< [out] ������ ������ ����� ('D'-����.������, 'M'-������ ����, 'C'-���, 'E'-���������� EMV, 'R'-���������� magstripe, 'F'-fallback)*/
  char   CardName[MAX_CARD_NAME_LEN]; /**< [out] �������� ���� ����� */
  char   AID[MAX_AID_ASCII_LEN];   /**< [out] Application ID ������� ����� (��� � ���� ASCIIZ-������)*/
  char   FullErrorText[MAX_FULL_ERROR_TEXT]; /**< [out] ������ ����� ��������� �� ������*/
  DWORD  GoodsPrice;                /**< [in] ���� �� ������� ������, ��� (34.99->3499)*/
  DWORD  GoodsVolume;               /**< [in] ���������� ������, � ���. ����� (30.234->30234)*/
  char   GoodsCode[MAX_GOODS_CODE+1]; /**< [in] ��� ������ �� ������� �������.*/
  char   GoodsName[MAX_GOODS_NAME]; /**< [in] ������������ ������ �� ������� �������. ��������! � ��������� auth_answer14 �������� ������ �� ���� ������ ������ ��� � gate.dll TGoodsData. ����������� ��� ������ ��� ��������*/
};

/** @brief ���������� �������� �� ������
 *  @param[in] track2 ������ ������� ����� � ��������� �������. ���� NULL, �� ����� ���������� ������� �����.
 *  @param[in,out] auth_answer ��. ::auth_answer14
 *  @param[in,out] payinfo ���������� ��� ��������� �������
 *  @return int ��� ������.
 */
PILOT_NT_API int  card_authorize14(
  char *track2,
  struct auth_answer14 *auth_answer,
  struct payment_info_item *payinfo
);


/** @brief ���������� �������� �� ������
 *  @note ������� ������������� ��������� ������� � �������� ��������� ��������. �� ������� ��������� � ���������� ���������� �������������� ��������� ��������
 *  � �������� ��������� ������������ ����������� ��������� ��������. ���������, ������� ����� �������� ��� �������� ����� �������� ��������
 *  ����������� � EParameterName.
 *  @param[in] track2 ������ ������� ����� � ��������� �������. ���� NULL, �� ����� ���������� ������� �����.
 *  @param[in,out] auth_answer ��. ::auth_answer14
 *  @param[in,out] payinfo ���������� ��� ��������� �������
 *  @param[in] dataIn ��. ::ctxAlloc
 *  @param[in] dataOut ��. ::ctxAlloc
 *  @return int ��� ������.
 */
PILOT_NT_API int  card_authorize15(
  char *track2,
  struct auth_answer14 *auth_answer,
  struct payment_info_item *payinfo,
  CONTEXT_PTR dataIn,
  CONTEXT_PTR dataOut
);

/**@}*/

/**
 * @defgroup SERVICE ��������� ��������
 */
/**@{*/

 /** @brief �������� ����� ��������� ��� ������
 *  @note ������� �� �������������� �� ��������� TTK ��� PCI-DSS �������.
 *  @param[out] pTerminalID ��������� ������������� ������ ���������. 9 ����.
 *  @return int ��� ������.
 */
PILOT_NT_API int GetTerminalID(char* pTerminalID);

/** @brief ������� � ����������� ���� �� �������
 *  @note �� ���������� ���� auth_answer.Check ����� ��������� ����� ��������� ��� ������.
 *  @param[out] auth_answer ����� ���������� ��������
 *  @return int ��� ������.
 */
PILOT_NT_API int ServiceMenu(struct auth_answer *auth_answer);
 
/** @brief �������� ���.
 *  @note  ���� TType, Amount, CType ��������� �� �����.
 *  @param[in,out] auth_answer ��. ::auth_answer
 *  @return int ��� ������.
 */
PILOT_NT_API int close_day(struct auth_answer *auth_answer);

/** @brief �������� ���.
 *  @note  ���� auth_answer::TType, auth_answer::Amount, auth_answer::CType ��������� �� �����.
 *  char* Check

�������� ����� ������ �� ������, ������� ���������� ��������� ������ ��������� �� ������, � ����� ���������� ������� ������� GlobalFree().

����� ����� �������� NULL. � ���� ������ ������� �������� � ��� ���������� ��������� ��������� �� ������.


 *  @param[in,out] auth_answer ��. ::auth_answer
 *  @param[in,out] iParams �������������� ���������� ��� �������� �� ���� ��������� (��������, � �������� ������� ����� �� �����).
 *  � ������� ������ �������������� ��������� ������ ������:
 *  1;�����_�����_��_��������;�����_�����_��_��������;����� �������� �����
 *  ����� 1 ���������, ��� ��������� ��� ��������� �������� ���������� �������� �������� � �� ����� � ��������.
 *  ������: �1;55;20010000;2334� - ��������, ��� �� ����� ���� 55 ����� ��������� �� ����� ����� 200100.00 ���, ����� �������� ����� 2334.
 *  �������� ����� ����� ��� ������������ ��� �������� ������������, ���� � ������� ����� ����������� ��������� ������ ������.
 *  @return int ��� ������.
 */
PILOT_NT_API int close_day_info(struct auth_answer *auth_answer, const char* iParams);

/** @brief ��������� �������� ������ �� ������� �����
 *  @param[in, out] auth_answer ��. auth_answer. ��� �������� ���� TType = 0 ����������� ������ �����, ����� - �������
 *  @return int ��� ������.
 */
PILOT_NT_API int get_statistics(struct auth_answer *auth_answer);

/** @brief ��������� ������ ������ ���������� pilot_nt.dll
 *  @return ������ ��� ����� ����� � ������� 0x00VVRRBB. VV - ������, RR - �����, BB - ������
 */
PILOT_NT_API unsigned int GetVer();

 /** @brief ���������� ���������������� ��������� � pinpad.ini
 *  @param[in] pConfData ������ ������� param1=value1;...paramN=valueN;
 *  @return int ��� ������.
 */
PILOT_NT_API int SetConfigData(const char* pConfData);

/** @brief ��������������� ���������� pilot_nt.dll
 *  @note ����������� ���������� �� ���������� gate.dll
 */
PILOT_NT_API void Done();

/** @brief ����������� ��������� ������ �����
 *  @param[in] hDestWindow ����� ����, ������� ����� �������� ��������� � ������ �����
 *  @param[in] message ������������� ��������� � ������ �����
 *  @return int ��� ������.
 */
PILOT_NT_API int EnableReader (HWND hDestWindow, UINT message);

/** @brief ����������� ���������� ������ �����
 *  @return int ��� ������.
 */
PILOT_NT_API int DisableReader();

/** @brief �������� ���������� �������
 *  @note ������� ��������� ������� �������. ��� �������� ���������� ���������� 0 (������ ���������), ��� ��������� � ��� ������ (������ �� ��������� ��� ����������).
 *  @return int ��� ������.
 */
PILOT_NT_API int TestPinpad();

/** @brief ������� ��������� ��������� �������� ���������� � ������������ ���������. ���� ���������� ��������� � ���� ���������, �� ��� ��������� ������ ����� � ������ ��� ����� ��������..
 *  @note ������� ������� ���������� ����� ��������� (����� � ��� �����������) �� ���������� � ��������� �������� ��������, ������� ���� ��������� ����� ����������. ���� ���� �� ���� �������� �� ���������, ������� ���������� ��� ������ 4140 � �� ��������� ������� ��������.
 *  @warning �� �������������� ��� ������ �� ��������� ���.
 *  @param dwAmount ����� �������� (� ��������)
 *  @param pAuthCode ��� �����������.
 *  @return int ��� ������.
 */
PILOT_NT_API int SuspendTrx (DWORD dwAmount, char* pAuthCode);

/** @brief ������� ���������� ��������� �������� ���������� � ����������� ���������.
 *  ����� ����� ���������� ����� �������� � ����� � ��������������� ��� ��������.
 *  ��������� �� ����� � ������������ ��������� ����� ��� ������.
 *  @note ������� ������� ���������� ����� ��������� (����� � ��� �����������) ��
 *  ���������� � ��������� �������� ��������, ������� ���� ��������� ����� ����������.
 *  ���� ���� �� ���� �������� �� ���������, ������� ���������� ��� ������ 4140 � �� ��������� ������� ��������.
 *  @warning �� �������������� ��� ������ �� ��������� ���.
 *  @param dwAmount ����� �������� (� ��������)
 *  @param pAuthCode ��� �����������.
 *  @return int ��� ������.
 */
PILOT_NT_API int CommitTrx  (DWORD dwAmount, char* pAuthCode);

/** @brief ������� �������� ����������� ������ ��������� �������� ��������
 *  @note �������� ����� ���� �������������� ��������, �����
 *  ������������ � ������������ ���������, ���� ��� � �� �����������). ���� ���������� ���
 *  ���� ���������� � ����������� ��������� �������� CommitTrx(), �� ������� RollbackTrx()
 *  ���������� � ����� ������ 4141, �� �������� ������� ��������. ������� ������� ����������
 *  ����� ��������� (����� � ��� �����������) �� ���������� � ��������� �������� ��������,
 *  ������� ���� ��������� ����� ����������. ���� ���� �� ������������ �� ���������, �������
 *  ���������� ��� ������ 4140 � �� ��������� ������� ��������.
 *  @warning �� �������������� ��� ������ �� ��������� ���.
 *  @param dwAmount ����� �������� (� ��������)
 *  @param pAuthCode ��� �����������.
 *  @return int ��� ������.
 */
PILOT_NT_API int RollbackTrx(DWORD dwAmount, char* pAuthCode);

/** @brief ������� ��������� ������ ������� card_authorizeX()
 *  @note ������� �� ����� ������� ��� ������� �� ���������� �����, ����� �������� ���������� ���������� ����� �� ������� card_authorize�(). ��� ���� ������� card_authorize�()  ���������� � ����� ������ 2000 (�������� ��������).
 *  @warning ������������ ������ � ����������� ��������.
 *  @return int ��� ������.
 */
PILOT_NT_API int AbortTransaction();

/** @brief ������� �������� � �������� �������� ���
 *  @note ������������ ������ ��������� ���� 62 ��. �������� � ������� \ref page6
 *  @param dwQueryRequestID ���������� ������������� �������� (requestID � ������ ���������� ��������)
 *  @param pCheque ��������� �� ������ � �������� �����
 *  @warning ������������ ������ � �������� �������� PCI DSS.
 *  @return int ��� ������.
 */
PILOT_NT_API int AddMerchantCheque(DWORD dwQueryRequestID, const char* pCheque);
/**@}*/

/**
 * @defgroup READCARD ������ �����
 */
/**@{*/
/** @brief ������ �����
 *  @param Last4Digits �����, ���� ������� ���������� ������ ��������� ����� ������ �����. ������ ������ ������ ���� �� ����� 5 ����.
 *  @param Hash ��� �� ������ �����, � ������� ASCII � ������� ������ � �����. ������ ������ ������ ���� �� ����� 41 �����.
 *  @return int ��� ������.
 */
PILOT_NT_API int ReadCard  (char *Last4Digits, char *Hash);

/** @brief ������� ��������� ��������� ���������� ����� ��� ������������� � ��������� ������� �������� �� ���������.
 *  @note ����� ������ ���� ������ ����������, � ��������� ������ ������� ������ ������.
 *  @param Last4Digits �����, ���� ������� ���������� ������ ��������� ����� ������ �����. ������ ������ ������ ���� �� ����� 5 ����.
 *  @param Hash ��� �� ������ �����, � ������� ASCII � ������� ������ � �����. ������ ������ ������ ���� �� ����� 41 �����.
 *  @return int ��� ������.
 */
PILOT_NT_API int ReadCardSB(char *Last4Digits, char *Hash);

/** @brief ������ �����
 *  @param Last4Digits �����, ���� ������� ���������� ������ ��������� ����� ������ �����. ������ ������ ������ ���� �� ����� 5 ����.
 *  @param Hash ��� �� ������ �����, � ������� ASCII � ������� ������ � �����. ������ ������ ������ ���� �� ����� 41 �����.
 *  @param pCardType ��� �����. ��. ::CardTypes
 *  @param pIsOwnCard ������� "����� �������� ����������"
 *  @return int ��� ������.
 */
PILOT_NT_API int ReadCardWithType(
  char *Last4Digits,
  char *Hash,
  int*  pCardType,
  int*  pIsOwnCard
);

/** @brief ������ �����
 *  @param PAN �����, ���� ������� ���������� PAN �����
 *  @param Hash ��� �� ������ �����, � ������� ASCII � ������� ������ � �����. ������ ������ ������ ���� �� ����� 41 �����.
 *  @param pCardType ��� �����. ��. ::CardTypes
 *  @param pIsOwnCard ������� "����� �������� ����������"
 *  @return int ��� ������.
 */
PILOT_NT_API int ReadMaskedCardWithType(
  char *PAN,
  char *Hash,
  int*  pCardType,
  int*  pIsOwnCard
);

/** @brief ������ ������ ������ ������� �����
 *  @note  ������ ������ ������� ����� ����� ����� �� 40 ��������.
 *  ������ ������� ����� ������:
 *    nnnn...nn=yymmddd...d
 *  ���     '=' - ������-�����������
 *      nnn...n - ����� �����
 *      yymm    - ���� �������� ����� (����)
 *      ddd...d - ��������� ������ �����
 *  @param[out] Track2 ����� �� 41 ����.
 *  @return int ��� ������.
 */
PILOT_NT_API int ReadTrack2(char *Track2);

/** @brief ������ ������ ������� ������� �����
 *  @note ������ ������� ������� ����� ����� ����� �� 40 ��������.
 *  @param[out] Last4Digits 4 ��������� ����� �����
 *  @param[out] Hash ��� �� ������ �����, � ������� ASCII � ������� ������ � �����. ������ ������ ������ ���� �� ����� 41 �����.
 *  @param[out] pTrack3 ������ ������� �����
 *  @return int ��� ������.
 */
PILOT_NT_API int ReadCardTrack3(char *Last4Digits, char *Hash, char* pTrack3);

/** @brief ������ ����� ��������
 *  @param[out] CardNo ������ ����� �����
 *  @param[out] ClientName ��� ������� ������� ���������������� �� �����
 *  @return int ��� ������.
 */
PILOT_NT_API int ReadSbercard(char *CardNo, char* ClientName);

/** @brief ������ ����� ��������
 *  @param[out] pTrack2 Track2
 *  @param[out] ValidThru ���� �������� ����� � ������� YYMM
 *  @param[out] pName ��� ������� ������� ���������������� �� �����
 *  @return int ��� ������.
 */
PILOT_NT_API int ReadCardAndName(
  char *pTrack2,
  char* ValidThru,
  char* pName
);

/** @brief ������ �����
 *  @note  ����� ������������ ��������� ��� �����������, �� ����� ����� �������������� ��� "CardNo=ValidThru".  
 *  ������� �� �������������� �� ��������� TTK ��� PCI-DSS �������.
 *  @param CardNo ����� �����. ����� ����� ����� �� 13 �� 19 ����.
 *  @param ValidThru ���� �������� ����� � ������� YYMM
 *  @return int ��� ������.
 */
PILOT_NT_API int ReadCardFull(char *CardNo, char *ValidThru);

/** @brief ������ �����
 *  @param dataOut �������� ��������, � ������� ���������� pan, ���, ��� �����, ������� "����� �������� ����������" � ����� ��������� ����������
 *  @return int ��� ������.
 */
PILOT_NT_API int ReadCardContext(CONTEXT_PTR dataOut);

 /** @brief ������ ������ ��������� ����� � �������� ����� ��������� �� ���������� �������.
  *  @note ������ ����� �������� �� ��������������� ��������. �������� "phone" ��� ����� ����������� ������,
  *  "email" ��� ����� ������ ����������� �����
  *  @param[in]     question     ������, ���� �������������� �������� (phone ��� email).
  *  @param[in|out] answer       ����� ��������� �����. ����� ��������� �������� �� ���������.
  *  @param[in]     answerLength ����� ������ ��� ������.
  *  @return int ��� ������.
 */
PILOT_NT_API int AskCardHolderAbout(const char* question, char* answer, unsigned answerLength);

/**@}*/

/**
 * @defgroup VENDING ����������� ��������
 */
/**@{*/
 /** @brief ���������� �������� ��� ������ �� �����
 *  @param[in] hText ������� ������ ������.
 *  @param[in] hEdit ������� ����� ������.
 *  @return int ��� ������.
 */
PILOT_NT_API int SetGUIHandles(int hText, int hEdit);

/** @brief ������� �����. ������� 5020.
 *  @return int ��� ������.
 */
PILOT_NT_API int EjectCard();

/** @brief ����������� ����� � ����� ��� ����������� ����. ������� 5021.
 *  @return int ��� ������.
 */
PILOT_NT_API int CaptureCard();

/** @brief �������� ������� ����� � ������� �����������.
 *  @return int ��� ������. 0 - ����� ������ ������, ������ � ������; 254 - ����� ���; 251 - ����� � ����� ������, �������, ��� �� ������� ������
 */
PILOT_NT_API int TestCard();

/** @brief ������� ���������� � ������������� ������
 *  @return int ��� ������.
 */
PILOT_NT_API int OpenKeyboard();

/** @brief ������� ����������
 *  @return int ��� ������.
 */
PILOT_NT_API int CloseKeyboard();

/** @brief �������� ��� �������� ������� ��� ��������
 *  @return int ������������ 0, ���� ������� ������� �� ����.
 */
PILOT_NT_API int ReadKeyboard();

/** @brief �������������� ���������� ������������
 *  @return unsigned char ���������� ������� �����.
 - 0x00 �� ������, �� ��������� �� �����
 - 0x01 ����� ������ ������
 - 0x02 ����� ������ ���������
 - 0x03 ����� � ������, � ���������
 */
PILOT_NT_API unsigned char TestHardware();
/** @brief ��������� �������� CloseReader ��� ������ �������� �������� �� ������� (sb_pilot 31)
 *  @return int ���������� ��� ������.
 */
PILOT_NT_API int PilotCloseReader();
/**@}*/

/**
 * @defgroup CONTEXT ������� ������ � ����������
 */
/**@{*/
 /** @brief ������� �������� ��������. ������� ������� ������ �������� ��������.
  *  @note ��� �������� ��������� �������� ���������� ��������������� ���������� ����������, ��� ��������� ��������� �������� ���������� ��������������� �����������.
  *  ��� ��������� ������������� ���������, ���� ���������� ��� ���� � ���������, ��� ����� ������������. ������������� ���� ��������� � ������� ��������� ��� ������
  *  ��������, ���� ������� �������� ������� ������� ctxClear ����� ��������� ��������������.
  *  @return CONTEXT_PTR ������������� ��������� �������� ��� 0, ���� ��������� ������
 */
PILOT_NT_API CONTEXT_PTR ctxAlloc(void);

 /** @brief ������� �������� ��������
  *  @param[in] ctx ������������� ���������.
  *  @return ���
 */
PILOT_NT_API void ctxFree(CONTEXT_PTR ctx);

 /** @brief ��������� ��������. ������� ������� ��� ��������� �� ���������.
  *  @param[in] ctx ������������� ���������.
  *  @return ���
 */
PILOT_NT_API void ctxClear(CONTEXT_PTR ctx);

 /** @brief �������� � �������� �������� ���������� ���������.
  *  @param[in] ctx  ������������� ���������.
  *  @param[in] name ������������� ���������.
  *  @param[in] str  ��������� �� ������.
  *  @return int ��� ������.
 */
PILOT_NT_API int ctxSetString(CONTEXT_PTR ctx, EParameterName name, const char* str);

 /** @brief �������� � �������� �������� �������������� ���������.
  *  @param[in] ctx  ������������� ���������.
  *  @param[in] name ������������� ���������.
  *  @param[in] val  �������� ���������.
  *  @return int ��� ������.
 */
PILOT_NT_API int ctxSetInt(CONTEXT_PTR ctx, EParameterName name, int val);

 /** @brief �������� � �������� �������� ��������� � ���� ������������������ ����.
  *  @param[in] ctx  ������������� ���������.
  *  @param[in] name ������������� ���������.
  *  @param[in] val  ��������� �� �����.
  *  @param[in] sz   ����� ������.
  *  @return int ��� ������.
 */
PILOT_NT_API int ctxSetBinary(CONTEXT_PTR ctx, EParameterName name, unsigned char* val, int sz);

 /** @brief ������� �� ��������� �������� ���������� � ���� ������.
  *  @note ��� ������������� ���������� �� �������� �� ��������� �������������, � ��� ������������������ ���� ������� ������ hex ������.
  *  @param[in] ctx  ������������� ���������.
  *  @param[in] name ������������� ���������.
  *  @param[in] val  ��������� �� ������.
  *  @param[in] sz   ����������� ��������� ����� ������.
  *  @return int ��� ������.
 */
PILOT_NT_API int ctxGetString(CONTEXT_PTR ctx, EParameterName name, char* str, int sz);

 /** @brief ������� �� ��������� �������� ���������� � ���� ������ �����.
  *  @note ��� ��������� ���������� ����� ��������� �������������� ������ � �����, ��� ������������������ ����
  *  ������� ����������� ������ ������ ����� ������������������ � ����� ����� � ������ �������� ����.
  *  @param[in] ctx  ������������� ���������.
  *  @param[in] name ������������� ���������.
  *  @param[in] pVal ��������� �� �����.
  *  @return int ��� ������.
 */
PILOT_NT_API int ctxGetInt   (CONTEXT_PTR ctx, EParameterName name, int* pVal);

 /** @brief ������� �� ��������� �������� ���������� � ���� ������������������ ����.
  *  @note ��� ��������� ���������� ����� �������� ����� ���������� ��� ���������, ��� ������������� ���������� �������
  *  ������ ������������������ �� ������� ���� � ������ �������� ����.
  *  @param[in] ctx     ������������� ���������.
  *  @param[in] name    ������������� ���������.
  *  @param[in] pVal    ��������� �� ����� ����������.
  *  @param[in] pOutSz  ���������� ����, ������������� � �����.
  *  @param[in] MAXSIZE ����������� ��������� ���������� ����.
  *  @return int ��� ������.
 */
PILOT_NT_API int ctxGetBinary(CONTEXT_PTR ctx, EParameterName name, unsigned char* pVal, int* pOutSz, int MAXSIZE);
/**@}*/

#pragma pack()

#ifdef __cplusplus
};
#endif

#endif // _PILOT_NT_H_

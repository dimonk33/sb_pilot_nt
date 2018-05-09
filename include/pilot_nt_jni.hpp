#pragma once
#include "pilot_nt.hpp"
#include "deprtmnt.hpp"

#define CARD_AUTHORIZE "_card_authorize"
#define ROLLBACK_TRX "_RollbackTrx"
#define TEST_PINPAD "_TestPinpad"
#define SERVICE_MENU "_ServiceMenu"
#define SET_CONFIG_DATA "_SetConfigData"
#define CLOSE_DAY "_close_day"
#define GET_STATISCTICS "_get_statistics"
#define ABORT_TRANSACTION "_AbortTransaction"
#define DDL_NAME L"native/windows/pilot/pilot_nt.dll"

namespace JNI {

	typedef int(*card_authorize_function)(char *track2, struct auth_answer *auth_answer);
	typedef int(*rollback_trx_function)(DWORD dwAmount, char* pAuthCode);
	typedef int(*test_function)();
	typedef int(*service_menu_function)(struct auth_answer *auth_answer);
	typedef int(*set_config_data_function)(const char *pConfData);
	typedef int(*close_day_function)(struct auth_answer *auth_answer);
	typedef int(*get_statistics_function)(struct auth_answer *auth_answer);
	typedef int(*abort_transaction_function)();

	class Pilot_NT_JNI {
		private:
			HMODULE dll;
		public:
			explicit Pilot_NT_JNI();
			int checkConnect();
			int rollbackLastTrx(DWORD amount);
			int setConfigs(const char *params);
			int cardOperation(int *typeOperation, int *amount);
			int closeDay();
			int getStatistics(bool *fullReport);
			int showServiceMenu();
			int abort();
			~Pilot_NT_JNI();
	};
}
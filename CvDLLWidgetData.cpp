#include "CvGameCoreDLL.h"
#include "CvGameCoreUtils.h"
#include "CvCity.h"
#include "CvUnit.h"
#include "CvGlobals.h"
#include "CvGameAI.h"
#include "CvMap.h"
#include "CvPlot.h"
#include "CvTeamAI.h"
#include "CvPlayerAI.h"
#include "CvGameCoreUtils.h"
#include "CyArgsList.h"
#include "CvGameTextMgr.h"
#include "CvDLLInterfaceIFaceBase.h"
#include "CvDLLPythonIFaceBase.h"
#include "CvDLLEngineIFaceBase.h"
#include "CvEventReporter.h"
#include "CvDLLWidgetData.h"
#include "CvPopupInfo.h"
#include "FProfiler.h"
#include "CvMessageControl.h"

CvDLLWidgetData* CvDLLWidgetData::m_pInst = NULL;

CvDLLWidgetData& CvDLLWidgetData::getInstance()
{
	if (m_pInst == NULL)
	{
		m_pInst = new CvDLLWidgetData;
	}
	return *m_pInst;
}

void CvDLLWidgetData::freeInstance()
{
	delete m_pInst;
	m_pInst = NULL;
}

void CvDLLWidgetData::parseHelp(CvWStringBuffer &szBuffer, CvWidgetDataStruct &widgetDataStruct)
{
	switch (widgetDataStruct.m_eWidgetType)
	{
	case WIDGET_PLOT_LIST:
		parsePlotListHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_PLOT_LIST_SHIFT:
		szBuffer.assign(gDLL->getText("TXT_KEY_MISC_CTRL_SHIFT", (GC.getDefineINT("MAX_PLOT_LIST_SIZE") - 1)));
		break;

	case WIDGET_CITY_SCROLL:
		break;

	case WIDGET_LIBERATE_CITY:
		parseLiberateCityHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_CITY_NAME:
		parseCityNameHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_UNIT_NAME:
		szBuffer.append(gDLL->getText("TXT_KEY_CHANGE_NAME"));
		break;

	case WIDGET_CREATE_GROUP:
		szBuffer.append(gDLL->getText("TXT_KEY_WIDGET_CREATE_GROUP"));
		break;

	case WIDGET_DELETE_GROUP:
		szBuffer.append(gDLL->getText("TXT_KEY_WIDGET_DELETE_GROUP"));
		break;

	case WIDGET_TRAIN:
		parseTrainHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_CONSTRUCT:
		parseConstructHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_CREATE:
		parseCreateHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_MAINTAIN:
		parseMaintainHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HURRY:
		parseHurryHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_MENU_ICON:
		szBuffer.append(gDLL->getText("TXT_KEY_MAIN_MENU"));

	case WIDGET_CONSCRIPT:
		parseConscriptHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_ACTION:
		parseActionHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_CITIZEN:
		parseCitizenHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_FREE_CITIZEN:
		parseFreeCitizenHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_DISABLED_CITIZEN:
		parseDisabledCitizenHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_ANGRY_CITIZEN:
		parseAngryCitizenHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_CHANGE_SPECIALIST:
		parseChangeSpecialistHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_RESEARCH:
		parseResearchHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_TECH_TREE:
		parseTechTreeHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_CHANGE_PERCENT:
		parseChangePercentHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_CITY_TAB:
		{
			CvWString szTemp;
            szTemp.Format(L"%s", GC.getCityTabInfo((CityTabTypes)widgetDataStruct.m_iData1).getDescription());
			szBuffer.assign(szTemp);
		}
		break;

	case WIDGET_CONTACT_CIV:
		parseContactCivHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_SCORE_BREAKDOWN:
		parseScoreHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_ZOOM_CITY:
		szBuffer.append(gDLL->getText("TXT_KEY_ZOOM_CITY_HELP"));
		break;

	case WIDGET_END_TURN:
		szBuffer.append(gDLL->getText("TXT_KEY_WIDGET_END_TURN"));
		break;
		
	case WIDGET_LAUNCH_VICTORY:
		szBuffer.append(gDLL->getText("TXT_KEY_WIDGET_LAUNCH_VICTORY"));
		break;

	case WIDGET_AUTOMATE_CITIZENS:
		parseAutomateCitizensHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_AUTOMATE_PRODUCTION:
		parseAutomateProductionHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_EMPHASIZE:
		parseEmphasizeHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_TRADE_ITEM:
		parseTradeItem(widgetDataStruct, szBuffer);
		break;

	case WIDGET_UNIT_MODEL:
		parseUnitModelHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_FLAG:
		parseFlagHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_MAINTENANCE:
		parseMaintenanceHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_RELIGION:
		parseReligionHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_RELIGION_CITY:
		parseReligionHelpCity(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_CORPORATION_CITY:
		parseCorporationHelpCity(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_NATIONALITY:
		parseNationalityHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_DEFENSE:
		break;

	case WIDGET_HELP_HEALTH:
		parseHealthHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_HAPPINESS:
		parseHappinessHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_POPULATION:
		parsePopulationHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_PRODUCTION:
		parseProductionHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_CULTURE:
		parseCultureHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_GREAT_PEOPLE:
		parseGreatPeopleHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_GREAT_GENERAL:
		parseGreatGeneralHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_SELECTED:
		parseSelectedHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_BUILDING:
		parseBuildingHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_TRADE_ROUTE_CITY:
		parseTradeRouteCityHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_ESPIONAGE_COST:
		parseEspionageCostHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_TECH_ENTRY:
		parseTechEntryHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_TECH_PREPREQ:
		parseTechPrereqHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_OBSOLETE:
		parseObsoleteHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_OBSOLETE_BONUS:
		parseObsoleteBonusString(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_OBSOLETE_SPECIAL:
		parseObsoleteSpecialHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_MOVE_BONUS:
		parseMoveHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_FREE_UNIT:
		parseFreeUnitHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_FEATURE_PRODUCTION:
		parseFeatureProductionHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_WORKER_RATE:
		parseWorkerRateHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_TRADE_ROUTES:
		parseTradeRouteHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_HEALTH_RATE:
		parseHealthRateHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_HAPPINESS_RATE:
		parseHappinessRateHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_FREE_TECH:
		parseFreeTechHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_LOS_BONUS:
		parseLOSHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_MAP_CENTER:
		parseMapCenterHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_MAP_REVEAL:
		parseMapRevealHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_MAP_TRADE:
		parseMapTradeHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_TECH_TRADE:
		parseTechTradeHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_GOLD_TRADE:
		parseGoldTradeHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_OPEN_BORDERS:
		parseOpenBordersHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_DEFENSIVE_PACT:
		parseDefensivePactHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_PERMANENT_ALLIANCE:
		parsePermanentAllianceHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_VASSAL_STATE:
		parseVassalStateHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_BUILD_BRIDGE:
		parseBuildBridgeHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_IRRIGATION:
		parseIrrigationHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_IGNORE_IRRIGATION:
		parseIgnoreIrrigationHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_WATER_WORK:
		parseWaterWorkHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_IMPROVEMENT:
		parseBuildHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_DOMAIN_EXTRA_MOVES:
		parseDomainExtraMovesHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_ADJUST:
		parseAdjustHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_TERRAIN_TRADE:
		parseTerrainTradeHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_SPECIAL_BUILDING:
		parseSpecialBuildingHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_YIELD_CHANGE:
		parseYieldChangeHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_BONUS_REVEAL:
		parseBonusRevealHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_CIVIC_REVEAL:
		parseCivicRevealHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_PROCESS_INFO:
		parseProcessInfoHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_FOUND_RELIGION:
		parseFoundReligionHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_FOUND_CORPORATION:
		parseFoundCorporationHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_FINANCE_NUM_UNITS:
		parseFinanceNumUnits(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_FINANCE_UNIT_COST:
		parseFinanceUnitCost(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_FINANCE_AWAY_SUPPLY:
		parseFinanceAwaySupply(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_FINANCE_CITY_MAINT:
		parseFinanceCityMaint(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_FINANCE_CIVIC_UPKEEP:
		parseFinanceCivicUpkeep(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_FINANCE_FOREIGN_INCOME:
		parseFinanceForeignIncome(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_FINANCE_INFLATED_COSTS:
		parseFinanceInflatedCosts(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_FINANCE_GROSS_INCOME:
		parseFinanceGrossIncome(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_FINANCE_NET_GOLD:
		parseFinanceNetGold(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_FINANCE_GOLD_RESERVE:
		parseFinanceGoldReserve(widgetDataStruct, szBuffer);
		break;

	case WIDGET_PEDIA_JUMP_TO_TECH:
		parseTechEntryHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_PEDIA_JUMP_TO_REQUIRED_TECH:
		parseTechTreePrereq(widgetDataStruct, szBuffer, false);
		break;

	case WIDGET_PEDIA_JUMP_TO_DERIVED_TECH:
		parseTechTreePrereq(widgetDataStruct, szBuffer, true);
		break;

	case WIDGET_PEDIA_JUMP_TO_UNIT:
		parseUnitHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_PEDIA_JUMP_TO_BUILDING:
		parseBuildingHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_PEDIA_BACK:
		// parsePediaBack(widgetDataStruct, szBuffer);
		break;

	case WIDGET_PEDIA_FORWARD:
		// parsePediaForward(widgetDataStruct, szBuffer);
		break;

	case WIDGET_PEDIA_JUMP_TO_BONUS:
		parseBonusHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_PEDIA_MAIN:
		break;

	case WIDGET_PEDIA_JUMP_TO_PROMOTION:
	case WIDGET_HELP_PROMOTION:
		parsePromotionHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_CHOOSE_EVENT:
		parseEventHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_PEDIA_JUMP_TO_UNIT_COMBAT:
		parseUnitCombatHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_PEDIA_JUMP_TO_IMPROVEMENT:
		parseImprovementHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_PEDIA_JUMP_TO_CIVIC:
		parseCivicHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_PEDIA_JUMP_TO_CIV:
		parseCivilizationHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_PEDIA_JUMP_TO_LEADER:
		parseLeaderHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_PEDIA_JUMP_TO_SPECIALIST:
		if (widgetDataStruct.m_iData1 != NO_SPECIALIST && widgetDataStruct.m_iData2 != 0)
		{
			CvWString szTemp;
			szTemp.Format(L"%s", GC.getSpecialistInfo((SpecialistTypes)widgetDataStruct.m_iData1).getDescription());
			szBuffer.assign(szTemp);
		}
		break;

	case WIDGET_PEDIA_JUMP_TO_PROJECT:
		parseProjectHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_PEDIA_JUMP_TO_RELIGION:
		parseReligionHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_PEDIA_JUMP_TO_CORPORATION:
		parseCorporationHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_PEDIA_JUMP_TO_TERRAIN:
		parseTerrainHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_PEDIA_JUMP_TO_FEATURE:
		parseFeatureHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_PEDIA_DESCRIPTION:
		parseDescriptionHelp(widgetDataStruct, szBuffer, false);
		break;

	case WIDGET_CLOSE_SCREEN:
		//parseCloseScreenHelp(szBuffer);
		break;

	case WIDGET_DEAL_KILL:
		parseKillDealHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_PEDIA_DESCRIPTION_NO_HELP:
		//parseDescriptionHelp(widgetDataStruct, szBuffer, true);
		break;

	case WIDGET_MINIMAP_HIGHLIGHT:
		break;

	case WIDGET_PRODUCTION_MOD_HELP:
		parseProductionModHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_LEADERHEAD:
		parseLeaderheadHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_LEADER_LINE:
		parseLeaderLineHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_COMMERCE_MOD_HELP:
		parseCommerceModHelp(widgetDataStruct, szBuffer);
		break;

	}
}

// Protected Functions...
bool CvDLLWidgetData::executeAction( CvWidgetDataStruct &widgetDataStruct )
{
	bool bHandled = false;			//	Right now general bHandled = false;  We can specific case this to true later.  Game will run with this = false;

	switch (widgetDataStruct.m_eWidgetType)
	{

	case WIDGET_PLOT_LIST:
		doPlotList(widgetDataStruct);
		break;

	case WIDGET_PLOT_LIST_SHIFT:
		gDLL->getInterfaceIFace()->changePlotListColumn(widgetDataStruct.m_iData1 * ((gDLL->ctrlKey()) ? (GC.getDefineINT("MAX_PLOT_LIST_SIZE") - 1) : 1));
		break;

	case WIDGET_CITY_SCROLL:
		if ( widgetDataStruct.m_iData1 > 0 )
		{
			GC.getGameINLINE().doControl(CONTROL_NEXTCITY);
		}
		else
		{
			GC.getGameINLINE().doControl(CONTROL_PREVCITY);
		}
		break;

	case WIDGET_LIBERATE_CITY:
		doLiberateCity();
		break;

	case WIDGET_CITY_NAME:
		doRenameCity();
		break;

	case WIDGET_UNIT_NAME:
		doRenameUnit();
		break;

	case WIDGET_CREATE_GROUP:
		doCreateGroup();
		break;

	case WIDGET_DELETE_GROUP:
		doDeleteGroup();
		break;

	case WIDGET_TRAIN:
		doTrain(widgetDataStruct);
		break;

	case WIDGET_CONSTRUCT:
		doConstruct(widgetDataStruct);
		break;

	case WIDGET_CREATE:
		doCreate(widgetDataStruct);
		break;

	case WIDGET_MAINTAIN:
		doMaintain(widgetDataStruct);
		break;

	case WIDGET_HURRY:
		doHurry(widgetDataStruct);
		break;

	case WIDGET_MENU_ICON:
		doMenu();

	case WIDGET_CONSCRIPT:
		doConscript();
		break;

	case WIDGET_ACTION:
		doAction(widgetDataStruct);
		break;

	case WIDGET_CITIZEN:
		break;

	case WIDGET_FREE_CITIZEN:
		break;

	case WIDGET_DISABLED_CITIZEN:
		break;

	case WIDGET_ANGRY_CITIZEN:
		break;

	case WIDGET_CHANGE_SPECIALIST:
		doChangeSpecialist(widgetDataStruct);
		break;

	case WIDGET_RESEARCH:
	case WIDGET_TECH_TREE:
		doResearch(widgetDataStruct);
		break;

	case WIDGET_CHANGE_PERCENT:
		doChangePercent(widgetDataStruct);
		break;

	case WIDGET_CITY_TAB:
		doCityTab(widgetDataStruct);
		break;

	case WIDGET_CONTACT_CIV:
		doContactCiv(widgetDataStruct);
		break;

	case WIDGET_END_TURN:
		GC.getGameINLINE().doControl(CONTROL_FORCEENDTURN);
		break;

	case WIDGET_LAUNCH_VICTORY:
		doLaunch(widgetDataStruct);
		break;

	case WIDGET_CONVERT:
		doConvert(widgetDataStruct);
		break;

	case WIDGET_REVOLUTION:
		// handled in Python
		break;

	case WIDGET_AUTOMATE_CITIZENS:
		doAutomateCitizens();
		break;

	case WIDGET_AUTOMATE_PRODUCTION:
		doAutomateProduction();
		break;

	case WIDGET_EMPHASIZE:
		doEmphasize(widgetDataStruct);
		break;

	case WIDGET_DIPLOMACY_RESPONSE:
		// CLEANUP -- PD
//		GC.getDiplomacyScreen().handleClick(m_pWidget);
		break;

	case WIDGET_TRADE_ITEM:
		break;

	case WIDGET_UNIT_MODEL:
		doUnitModel();
		break;

	case WIDGET_FLAG:
		doFlag();
		break;

	case WIDGET_HELP_SELECTED:
		doSelected(widgetDataStruct);
		break;

	case WIDGET_PEDIA_JUMP_TO_UNIT:
		doPediaUnitJump(widgetDataStruct);
		break;

	case WIDGET_PEDIA_JUMP_TO_BUILDING:
		doPediaBuildingJump(widgetDataStruct);
		break;

	case WIDGET_PEDIA_JUMP_TO_TECH:
	case WIDGET_PEDIA_JUMP_TO_REQUIRED_TECH:
	case WIDGET_PEDIA_JUMP_TO_DERIVED_TECH:
		doPediaTechJump(widgetDataStruct);
		break;

	case WIDGET_PEDIA_BACK:
		doPediaBack();
		break;
	case WIDGET_PEDIA_FORWARD:
		doPediaForward();
		break;

	case WIDGET_PEDIA_JUMP_TO_BONUS:
		doPediaBonusJump(widgetDataStruct);
		break;

	case WIDGET_PEDIA_MAIN:
		doPediaMain(widgetDataStruct);
		break;

	case WIDGET_PEDIA_JUMP_TO_PROMOTION:
		doPediaPromotionJump(widgetDataStruct);
		break;

	case WIDGET_PEDIA_JUMP_TO_UNIT_COMBAT:
		doPediaUnitCombatJump(widgetDataStruct);
		break;

	case WIDGET_PEDIA_JUMP_TO_IMPROVEMENT:
		doPediaImprovementJump(widgetDataStruct);
		break;

	case WIDGET_PEDIA_JUMP_TO_CIVIC:
		doPediaCivicJump(widgetDataStruct);
		break;

	case WIDGET_PEDIA_JUMP_TO_CIV:
		doPediaCivilizationJump(widgetDataStruct);
		break;

	case WIDGET_PEDIA_JUMP_TO_LEADER:
		doPediaLeaderJump(widgetDataStruct);
		break;

	case WIDGET_PEDIA_JUMP_TO_SPECIALIST:
		doPediaSpecialistJump(widgetDataStruct);
		break;

	case WIDGET_PEDIA_JUMP_TO_PROJECT:
		doPediaProjectJump(widgetDataStruct);
		break;

	case WIDGET_PEDIA_JUMP_TO_RELIGION:
		doPediaReligionJump(widgetDataStruct);
		break;

	case WIDGET_PEDIA_JUMP_TO_CORPORATION:
		doPediaCorporationJump(widgetDataStruct);
		break;

	case WIDGET_PEDIA_JUMP_TO_TERRAIN:
		doPediaTerrainJump(widgetDataStruct);
		break;

	case WIDGET_PEDIA_JUMP_TO_FEATURE:
		doPediaFeatureJump(widgetDataStruct);
		break;

	case WIDGET_PEDIA_DESCRIPTION:
	case WIDGET_PEDIA_DESCRIPTION_NO_HELP:
		doPediaDescription(widgetDataStruct);
		break;

	case WIDGET_TURN_EVENT:
		doGotoTurnEvent(widgetDataStruct);
		break;

	case WIDGET_FOREIGN_ADVISOR:
		doForeignAdvisor(widgetDataStruct);
		break;

	case WIDGET_DEAL_KILL:
		doDealKill(widgetDataStruct);
		break;

	case WIDGET_MINIMAP_HIGHLIGHT:
		doRefreshMilitaryAdvisor(widgetDataStruct);
		break;

	case WIDGET_CHOOSE_EVENT:
		break;

	case WIDGET_ZOOM_CITY:
		break;

	case WIDGET_HELP_TECH_PREPREQ:
	case WIDGET_HELP_OBSOLETE:
	case WIDGET_HELP_OBSOLETE_BONUS:
	case WIDGET_HELP_OBSOLETE_SPECIAL:
	case WIDGET_HELP_MOVE_BONUS:
	case WIDGET_HELP_FREE_UNIT:
	case WIDGET_HELP_FEATURE_PRODUCTION:
	case WIDGET_HELP_WORKER_RATE:
	case WIDGET_HELP_TRADE_ROUTES:
	case WIDGET_HELP_HEALTH_RATE:
	case WIDGET_HELP_HAPPINESS_RATE:
	case WIDGET_HELP_FREE_TECH:
	case WIDGET_HELP_LOS_BONUS:
	case WIDGET_HELP_MAP_CENTER:
	case WIDGET_HELP_MAP_REVEAL:
	case WIDGET_HELP_MAP_TRADE:
	case WIDGET_HELP_TECH_TRADE:
	case WIDGET_HELP_GOLD_TRADE:
	case WIDGET_HELP_OPEN_BORDERS:
	case WIDGET_HELP_DEFENSIVE_PACT:
	case WIDGET_HELP_PERMANENT_ALLIANCE:
	case WIDGET_HELP_VASSAL_STATE:
	case WIDGET_HELP_BUILD_BRIDGE:
	case WIDGET_HELP_IRRIGATION:
	case WIDGET_HELP_IGNORE_IRRIGATION:
	case WIDGET_HELP_WATER_WORK:
	case WIDGET_HELP_IMPROVEMENT:
	case WIDGET_HELP_DOMAIN_EXTRA_MOVES:
	case WIDGET_HELP_ADJUST:
	case WIDGET_HELP_TERRAIN_TRADE:
	case WIDGET_HELP_SPECIAL_BUILDING:
	case WIDGET_HELP_YIELD_CHANGE:
	case WIDGET_HELP_BONUS_REVEAL:
	case WIDGET_HELP_CIVIC_REVEAL:
	case WIDGET_HELP_PROCESS_INFO:
	case WIDGET_HELP_FINANCE_NUM_UNITS:
	case WIDGET_HELP_FINANCE_UNIT_COST:
	case WIDGET_HELP_FINANCE_AWAY_SUPPLY:
	case WIDGET_HELP_FINANCE_CITY_MAINT:
	case WIDGET_HELP_FINANCE_CIVIC_UPKEEP:
	case WIDGET_HELP_FINANCE_FOREIGN_INCOME:
	case WIDGET_HELP_FINANCE_INFLATED_COSTS:
	case WIDGET_HELP_FINANCE_GROSS_INCOME:
	case WIDGET_HELP_FINANCE_NET_GOLD:
	case WIDGET_HELP_FINANCE_GOLD_RESERVE:
	case WIDGET_HELP_RELIGION_CITY:
	case WIDGET_HELP_CORPORATION_CITY:
	case WIDGET_HELP_PROMOTION:
	case WIDGET_LEADERHEAD:
	case WIDGET_LEADER_LINE:
	case WIDGET_CLOSE_SCREEN:
	case WIDGET_SCORE_BREAKDOWN:
		//	Nothing on clicked
		break;
	}

	return bHandled;
}

//	right clicking action
bool CvDLLWidgetData::executeAltAction( CvWidgetDataStruct &widgetDataStruct )
{
	CvWidgetDataStruct widgetData = widgetDataStruct;

	bool bHandled = true;
	switch (widgetDataStruct.m_eWidgetType)
	{
	case WIDGET_HELP_TECH_ENTRY:
	case WIDGET_HELP_TECH_PREPREQ:
	case WIDGET_RESEARCH:
	case WIDGET_TECH_TREE:
		doPediaTechJump(widgetDataStruct);
		break;
	case WIDGET_TRAIN:
		doPediaTrainJump(widgetDataStruct);
		break;
	case WIDGET_CONSTRUCT:
		doPediaConstructJump(widgetDataStruct);
		break;
	case WIDGET_CREATE:
		doPediaProjectJump(widgetDataStruct);
		break;
	case WIDGET_PEDIA_JUMP_TO_UNIT:
	case WIDGET_HELP_FREE_UNIT:
		doPediaUnitJump(widgetDataStruct);
		break;
	case WIDGET_HELP_FOUND_RELIGION:
		widgetData.m_iData1 = widgetData.m_iData2;
		//	Intentional fallthrough...
	case WIDGET_PEDIA_JUMP_TO_RELIGION:
		doPediaReligionJump(widgetData);
		break;
	case WIDGET_HELP_FOUND_CORPORATION:
		widgetData.m_iData1 = widgetData.m_iData2;
		//	Intentional fallthrough...
	case WIDGET_PEDIA_JUMP_TO_CORPORATION:
		doPediaCorporationJump(widgetData);
		break;
	case WIDGET_PEDIA_JUMP_TO_BUILDING:
		doPediaBuildingJump(widgetDataStruct);
		break;
	case WIDGET_PEDIA_JUMP_TO_PROMOTION:
		doPediaPromotionJump(widgetDataStruct);
		break;
	case WIDGET_HELP_OBSOLETE:
		doPediaBuildingJump(widgetDataStruct);
		break;
	case WIDGET_HELP_IMPROVEMENT:
		doPediaBuildJump(widgetDataStruct);
		break;
	case WIDGET_HELP_YIELD_CHANGE:
		doPediaImprovementJump(widgetDataStruct, true);
		break;
	case WIDGET_HELP_BONUS_REVEAL:
	case WIDGET_HELP_OBSOLETE_BONUS:
		doPediaBonusJump(widgetDataStruct, true);
		break;
	case WIDGET_CITIZEN:
	case WIDGET_FREE_CITIZEN:
	case WIDGET_DISABLED_CITIZEN:
		doPediaSpecialistJump(widgetDataStruct);
		break;
	case WIDGET_PEDIA_JUMP_TO_PROJECT:
		doPediaProjectJump(widgetDataStruct);
		break;
	case WIDGET_HELP_CIVIC_REVEAL:
		widgetData.m_iData1 = widgetData.m_iData2;
		doPediaCivicJump(widgetData);
		break;
	case WIDGET_LEADERHEAD:
		doContactCiv(widgetDataStruct);
		break;

	default:
		bHandled = false;
		break;
	}

	return (bHandled);
}

bool CvDLLWidgetData::isLink(const CvWidgetDataStruct &widgetDataStruct) const
{
	bool bLink = false;
	switch (widgetDataStruct.m_eWidgetType)
	{
	case WIDGET_PEDIA_JUMP_TO_TECH:
	case WIDGET_PEDIA_JUMP_TO_REQUIRED_TECH:
	case WIDGET_PEDIA_JUMP_TO_DERIVED_TECH:
	case WIDGET_PEDIA_JUMP_TO_BUILDING:
	case WIDGET_PEDIA_JUMP_TO_UNIT:
	case WIDGET_PEDIA_JUMP_TO_UNIT_COMBAT:
	case WIDGET_PEDIA_JUMP_TO_PROMOTION:
	case WIDGET_PEDIA_JUMP_TO_BONUS:
	case WIDGET_PEDIA_JUMP_TO_IMPROVEMENT:
	case WIDGET_PEDIA_JUMP_TO_CIVIC:
	case WIDGET_PEDIA_JUMP_TO_CIV:
	case WIDGET_PEDIA_JUMP_TO_LEADER:
	case WIDGET_PEDIA_JUMP_TO_SPECIALIST:
	case WIDGET_PEDIA_JUMP_TO_PROJECT:
	case WIDGET_PEDIA_JUMP_TO_RELIGION:
	case WIDGET_PEDIA_JUMP_TO_CORPORATION:
	case WIDGET_PEDIA_JUMP_TO_TERRAIN:
	case WIDGET_PEDIA_JUMP_TO_FEATURE:
	case WIDGET_PEDIA_FORWARD:
	case WIDGET_PEDIA_BACK:
	case WIDGET_PEDIA_MAIN:
	case WIDGET_TURN_EVENT:
	case WIDGET_FOREIGN_ADVISOR:
	case WIDGET_PEDIA_DESCRIPTION:
	case WIDGET_PEDIA_DESCRIPTION_NO_HELP:
	case WIDGET_MINIMAP_HIGHLIGHT:
		bLink = (widgetDataStruct.m_iData1 >= 0);
		break;
	case WIDGET_DEAL_KILL:
		{
			CvDeal* pDeal = GC.getGameINLINE().getDeal(widgetDataStruct.m_iData1);
			bLink = (NULL != pDeal && pDeal->isCancelable(GC.getGameINLINE().getActivePlayer()));
		}
		break;
	case WIDGET_CONVERT:
		bLink = (0 != widgetDataStruct.m_iData2);
		break;
	case WIDGET_GENERAL:
	case WIDGET_REVOLUTION:
		bLink = (1 == widgetDataStruct.m_iData1);
		break;
	}
	return (bLink);
}


void CvDLLWidgetData::doPlotList(CvWidgetDataStruct &widgetDataStruct)
{
	PROFILE_FUNC();

	CvUnit* pUnit;
	bool bWasCityScreenUp;

	int iUnitIndex = widgetDataStruct.m_iData1 + gDLL->getInterfaceIFace()->getPlotListColumn() - gDLL->getInterfaceIFace()->getPlotListOffset();

	CvPlot *selectionPlot = gDLL->getInterfaceIFace()->getSelectionPlot();
	pUnit = gDLL->getInterfaceIFace()->getInterfacePlotUnit(selectionPlot, iUnitIndex);

	if (pUnit != NULL)
	{
		if (pUnit->getOwnerINLINE() == GC.getGameINLINE().getActivePlayer())
		{
			bWasCityScreenUp = gDLL->getInterfaceIFace()->isCityScreenUp();

			gDLL->getInterfaceIFace()->selectGroup(pUnit, gDLL->shiftKey(), gDLL->ctrlKey(), gDLL->altKey());

			if (bWasCityScreenUp)
			{
				gDLL->getInterfaceIFace()->lookAtSelectionPlot();
			}
		}
	}
}


void CvDLLWidgetData::doLiberateCity()
{
	GC.getGameINLINE().selectedCitiesGameNetMessage(GAMEMESSAGE_DO_TASK, TASK_LIBERATE, 0);

	gDLL->getInterfaceIFace()->clearSelectedCities();
}


void CvDLLWidgetData::doRenameCity()
{
	CvCity* pHeadSelectedCity;

	pHeadSelectedCity = gDLL->getInterfaceIFace()->getHeadSelectedCity();

	if (pHeadSelectedCity != NULL)
	{
		if (pHeadSelectedCity->getOwnerINLINE() == GC.getGameINLINE().getActivePlayer())
		{
			CvEventReporter::getInstance().cityRename(pHeadSelectedCity);
		}
	}
}


void CvDLLWidgetData::doRenameUnit()
{
	CvUnit* pHeadSelectedUnit;

	pHeadSelectedUnit = gDLL->getInterfaceIFace()->getHeadSelectedUnit();

	if (pHeadSelectedUnit != NULL)
	{
		if (pHeadSelectedUnit->getOwnerINLINE() == GC.getGameINLINE().getActivePlayer())
		{
			CvEventReporter::getInstance().unitRename(pHeadSelectedUnit);
		}
	}
}


void CvDLLWidgetData::doCreateGroup()
{
	GC.getGameINLINE().selectionListGameNetMessage(GAMEMESSAGE_JOIN_GROUP);
}


void CvDLLWidgetData::doDeleteGroup()
{
	GC.getGameINLINE().selectionListGameNetMessage(GAMEMESSAGE_JOIN_GROUP, -1, -1, -1, 0, false, true);
}


void CvDLLWidgetData::doTrain(CvWidgetDataStruct &widgetDataStruct)
{
	UnitTypes eUnit;

	eUnit = ((UnitTypes)(GC.getCivilizationInfo(GC.getGameINLINE().getActiveCivilizationType()).getCivilizationUnits(widgetDataStruct.m_iData1)));

	if (widgetDataStruct.m_iData2 != FFreeList::INVALID_INDEX)
	{
		CvMessageControl::getInstance().sendPushOrder(widgetDataStruct.m_iData2, ORDER_TRAIN, eUnit, false, false, false);
	}
	else
	{
		GC.getGameINLINE().selectedCitiesGameNetMessage(GAMEMESSAGE_PUSH_ORDER, ORDER_TRAIN, eUnit, -1, false, gDLL->altKey(), gDLL->shiftKey(), gDLL->ctrlKey());
	}

	gDLL->getInterfaceIFace()->setCityTabSelectionRow(CITYTAB_UNITS);
}


void CvDLLWidgetData::doConstruct(CvWidgetDataStruct &widgetDataStruct)
{
	BuildingTypes eBuilding;

	eBuilding = ((BuildingTypes)(GC.getCivilizationInfo(GC.getGameINLINE().getActiveCivilizationType()).getCivilizationBuildings(widgetDataStruct.m_iData1)));

	if (widgetDataStruct.m_iData2 != FFreeList::INVALID_INDEX)
	{
		CvMessageControl::getInstance().sendPushOrder(widgetDataStruct.m_iData2, ORDER_CONSTRUCT, eBuilding, false, false, false);
	}
	else
	{
		GC.getGameINLINE().selectedCitiesGameNetMessage(GAMEMESSAGE_PUSH_ORDER, ORDER_CONSTRUCT, eBuilding, -1, false, gDLL->altKey(), gDLL->shiftKey(), gDLL->ctrlKey());
	}

	if (isLimitedWonderClass((BuildingClassTypes)(widgetDataStruct.m_iData1)))
	{
		gDLL->getInterfaceIFace()->setCityTabSelectionRow(CITYTAB_WONDERS);
	}
	else
	{
		gDLL->getInterfaceIFace()->setCityTabSelectionRow(CITYTAB_BUILDINGS);
	}
}


void CvDLLWidgetData::doCreate(CvWidgetDataStruct &widgetDataStruct)
{
	if (widgetDataStruct.m_iData2 != FFreeList::INVALID_INDEX)
	{
		CvMessageControl::getInstance().sendPushOrder(widgetDataStruct.m_iData2, ORDER_CREATE, widgetDataStruct.m_iData1, false, false, false);
	}
	else
	{
		GC.getGameINLINE().selectedCitiesGameNetMessage(GAMEMESSAGE_PUSH_ORDER, ORDER_CREATE, widgetDataStruct.m_iData1, -1, false, gDLL->altKey(), gDLL->shiftKey(), gDLL->ctrlKey());
	}

	gDLL->getInterfaceIFace()->setCityTabSelectionRow(CITYTAB_WONDERS);
}


void CvDLLWidgetData::doMaintain(CvWidgetDataStruct &widgetDataStruct)
{
	if (widgetDataStruct.m_iData2 != FFreeList::INVALID_INDEX)
	{
		CvMessageControl::getInstance().sendPushOrder(widgetDataStruct.m_iData2, ORDER_MAINTAIN, widgetDataStruct.m_iData1, false, false, false);
	}
	else
	{
		GC.getGameINLINE().selectedCitiesGameNetMessage(GAMEMESSAGE_PUSH_ORDER, ORDER_MAINTAIN, widgetDataStruct.m_iData1, -1, false, gDLL->altKey(), gDLL->shiftKey(), gDLL->ctrlKey());
	}

	gDLL->getInterfaceIFace()->setCityTabSelectionRow(CITYTAB_WONDERS);
}


void CvDLLWidgetData::doHurry(CvWidgetDataStruct &widgetDataStruct)
{
	GC.getGameINLINE().selectedCitiesGameNetMessage(GAMEMESSAGE_DO_TASK, TASK_HURRY, widgetDataStruct.m_iData1);
}


void CvDLLWidgetData::doConscript()
{
	GC.getGameINLINE().selectedCitiesGameNetMessage(GAMEMESSAGE_DO_TASK, TASK_CONSCRIPT);
}


void CvDLLWidgetData::doAction(CvWidgetDataStruct &widgetDataStruct)
{
	GC.getGameINLINE().handleAction(widgetDataStruct.m_iData1);
}


void CvDLLWidgetData::doChangeSpecialist(CvWidgetDataStruct &widgetDataStruct)
{
	GC.getGameINLINE().selectedCitiesGameNetMessage(GAMEMESSAGE_DO_TASK, TASK_CHANGE_SPECIALIST, widgetDataStruct.m_iData1, widgetDataStruct.m_iData2);
}


void CvDLLWidgetData::doResearch(CvWidgetDataStruct &widgetDataStruct)
{
	bool bShift;

	bShift = gDLL->shiftKey();

	if (!bShift)
	{
		if ((GetKeyState(VK_LSHIFT) & 0x8000) || (GetKeyState(VK_RSHIFT) & 0x8000))
		{
			bShift = true;
		}
	}

	// RBMP Free Tech Popup Fix
	if (widgetDataStruct.m_iData2 > 0)
	{
		CvPlayer& kPlayer = GET_PLAYER(GC.getGameINLINE().getActivePlayer());

		if (!kPlayer.isChoosingFreeTech())
		{
			gDLL->getInterfaceIFace()->addMessage(GC.getGameINLINE().getActivePlayer(), true, GC.getEVENT_MESSAGE_TIME(), gDLL->getText("TXT_KEY_CHEATERS_NEVER_PROSPER"), NULL, MESSAGE_TYPE_MAJOR_EVENT);
			return;
		}
		else
		{
			kPlayer.setChoosingFreeTech(false);
		}
	}

	CvMessageControl::getInstance().sendResearch(((TechTypes)widgetDataStruct.m_iData1), widgetDataStruct.m_iData2, bShift);
}


void CvDLLWidgetData::doChangePercent(CvWidgetDataStruct &widgetDataStruct)
{
	CvMessageControl::getInstance().sendPercentChange(((CommerceTypes)widgetDataStruct.m_iData1), widgetDataStruct.m_iData2);
}

void CvDLLWidgetData::doCityTab(CvWidgetDataStruct &widgetDataStruct)
{
	gDLL->getInterfaceIFace()->setCityTabSelectionRow((CityTabTypes)widgetDataStruct.m_iData1);
}

void CvDLLWidgetData::doContactCiv(CvWidgetDataStruct &widgetDataStruct)
{
	if (gDLL->isDiplomacy() || gDLL->isMPDiplomacyScreenUp())
	{
		return;
	}

	//	Do not execute this if we are trying to contact ourselves...
	if (GC.getGameINLINE().getActivePlayer() == widgetDataStruct.m_iData1)
	{
		if (!gDLL->getInterfaceIFace()->isFocusedWidget())
		{
			gDLL->getInterfaceIFace()->toggleScoresMinimized();
		}

		return;
	}

	if (gDLL->shiftKey())
	{
		if (GET_PLAYER((PlayerTypes)widgetDataStruct.m_iData1).isHuman())
		{
			if (widgetDataStruct.m_iData1 != GC.getGameINLINE().getActivePlayer())
			{
				gDLL->getInterfaceIFace()->showTurnLog((ChatTargetTypes)widgetDataStruct.m_iData1);
			}
		}
		return;
	}

	if (gDLL->altKey())
	{
		if (GET_TEAM(GC.getGameINLINE().getActiveTeam()).canDeclareWar(GET_PLAYER((PlayerTypes)widgetDataStruct.m_iData1).getTeam()))
		{
			CvMessageControl::getInstance().sendChangeWar(GET_PLAYER((PlayerTypes)widgetDataStruct.m_iData1).getTeam(), true);
		}
		else if (GET_TEAM(GET_PLAYER((PlayerTypes)widgetDataStruct.m_iData1).getTeam()).isVassal(GC.getGameINLINE().getActiveTeam()))
		{
			CvPopupInfo* pInfo = new CvPopupInfo(BUTTONPOPUP_VASSAL_DEMAND_TRIBUTE, widgetDataStruct.m_iData1);
			if (pInfo)
			{
				gDLL->getInterfaceIFace()->addPopup(pInfo, GC.getGameINLINE().getActivePlayer(), true);
			}
		}
		return;
	}

	GET_PLAYER(GC.getGameINLINE().getActivePlayer()).contact((PlayerTypes)widgetDataStruct.m_iData1);
}

void CvDLLWidgetData::doConvert(CvWidgetDataStruct &widgetDataStruct)
{
	if (widgetDataStruct.m_iData2 != 0)
	{
		CvMessageControl::getInstance().sendConvert((ReligionTypes)(widgetDataStruct.m_iData1));
	}
}

void CvDLLWidgetData::doAutomateCitizens()
{
	CvCity* pHeadSelectedCity;

	pHeadSelectedCity = gDLL->getInterfaceIFace()->getHeadSelectedCity();

	if (pHeadSelectedCity != NULL)
	{
		GC.getGameINLINE().selectedCitiesGameNetMessage(GAMEMESSAGE_DO_TASK, TASK_SET_AUTOMATED_CITIZENS, -1, -1, !(pHeadSelectedCity->isCitizensAutomated()));
	}
}

void CvDLLWidgetData::doAutomateProduction()
{
	CvCity* pHeadSelectedCity;

	pHeadSelectedCity = gDLL->getInterfaceIFace()->getHeadSelectedCity();

	if (pHeadSelectedCity != NULL)
	{
		GC.getGameINLINE().selectedCitiesGameNetMessage(GAMEMESSAGE_DO_TASK, TASK_SET_AUTOMATED_PRODUCTION, -1, -1, !pHeadSelectedCity->isProductionAutomated(), gDLL->altKey(), gDLL->shiftKey(), gDLL->ctrlKey());
	}
}

void CvDLLWidgetData::doEmphasize(CvWidgetDataStruct &widgetDataStruct)
{
	CvCity* pHeadSelectedCity;

	pHeadSelectedCity = gDLL->getInterfaceIFace()->getHeadSelectedCity();

	if (pHeadSelectedCity != NULL)
	{
		GC.getGameINLINE().selectedCitiesGameNetMessage(GAMEMESSAGE_DO_TASK, TASK_SET_EMPHASIZE, widgetDataStruct.m_iData1, -1, !(pHeadSelectedCity->AI_isEmphasize((EmphasizeTypes)(widgetDataStruct.m_iData1))));
	}
}

void CvDLLWidgetData::doUnitModel()
{
	if (gDLL->getInterfaceIFace()->isFocused())
	{
		//	Do NOT execute if a screen is up...
		return;
	}

	gDLL->getInterfaceIFace()->lookAtSelectionPlot();
}


void CvDLLWidgetData::doFlag()
{
	GC.getGameINLINE().doControl(CONTROL_SELECTCAPITAL);
}

void CvDLLWidgetData::doSelected(CvWidgetDataStruct &widgetDataStruct)
{
	CvCity* pHeadSelectedCity;

	pHeadSelectedCity = gDLL->getInterfaceIFace()->getHeadSelectedCity();

	if (pHeadSelectedCity != NULL)
	{
		GC.getGameINLINE().selectedCitiesGameNetMessage(GAMEMESSAGE_POP_ORDER, widgetDataStruct.m_iData1);
	}
}


void CvDLLWidgetData::doPediaTechJump(CvWidgetDataStruct &widgetDataStruct)
{
	CyArgsList argsList;
	argsList.add(widgetDataStruct.m_iData1);
	gDLL->getPythonIFace()->callFunction(PYScreensModule, "pediaJumpToTech", argsList.makeFunctionArgs());
}

void CvDLLWidgetData::doPediaUnitJump(CvWidgetDataStruct &widgetDataStruct)
{
	CyArgsList argsList;

	argsList.add(widgetDataStruct.m_iData1);
	gDLL->getPythonIFace()->callFunction(PYScreensModule, "pediaJumpToUnit", argsList.makeFunctionArgs());
}

void CvDLLWidgetData::doPediaBuildingJump(CvWidgetDataStruct &widgetDataStruct)
{
	CyArgsList argsList;
	argsList.add(widgetDataStruct.m_iData1);
	gDLL->getPythonIFace()->callFunction(PYScreensModule, "pediaJumpToBuilding", argsList.makeFunctionArgs());
}

void CvDLLWidgetData::doPediaProjectJump(CvWidgetDataStruct &widgetDataStruct)
{
	CyArgsList argsList;
	argsList.add(widgetDataStruct.m_iData1);
	gDLL->getPythonIFace()->callFunction(PYScreensModule, "pediaJumpToProject", argsList.makeFunctionArgs());
}

void CvDLLWidgetData::doPediaReligionJump(CvWidgetDataStruct &widgetDataStruct)
{
	CyArgsList argsList;
	argsList.add(widgetDataStruct.m_iData1);
	gDLL->getPythonIFace()->callFunction(PYScreensModule, "pediaJumpToReligion", argsList.makeFunctionArgs());
}

void CvDLLWidgetData::doPediaCorporationJump(CvWidgetDataStruct &widgetDataStruct)
{
	CyArgsList argsList;
	argsList.add(widgetDataStruct.m_iData1);
	gDLL->getPythonIFace()->callFunction(PYScreensModule, "pediaJumpToCorporation", argsList.makeFunctionArgs());
}

void CvDLLWidgetData::doPediaTerrainJump(CvWidgetDataStruct &widgetDataStruct)
{
	CyArgsList argsList;
	argsList.add(widgetDataStruct.m_iData1);
	gDLL->getPythonIFace()->callFunction(PYScreensModule, "pediaJumpToTerrain", argsList.makeFunctionArgs());
}

void CvDLLWidgetData::doPediaFeatureJump(CvWidgetDataStruct &widgetDataStruct)
{
	CyArgsList argsList;
	argsList.add(widgetDataStruct.m_iData1);
	gDLL->getPythonIFace()->callFunction(PYScreensModule, "pediaJumpToFeature", argsList.makeFunctionArgs());
}

void CvDLLWidgetData::doPediaTrainJump(CvWidgetDataStruct &widgetDataStruct)
{
	CyArgsList argsList;
	argsList.add(GC.getCivilizationInfo(GC.getGameINLINE().getActiveCivilizationType()).getCivilizationUnits(widgetDataStruct.m_iData1));
	
	gDLL->getPythonIFace()->callFunction(PYScreensModule, "pediaJumpToUnit", argsList.makeFunctionArgs());
}


void CvDLLWidgetData::doPediaConstructJump(CvWidgetDataStruct &widgetDataStruct)
{
	CyArgsList argsList;
	argsList.add(GC.getCivilizationInfo(GC.getGameINLINE().getActiveCivilizationType()).getCivilizationBuildings(widgetDataStruct.m_iData1));

	gDLL->getPythonIFace()->callFunction(PYScreensModule, "pediaJumpToBuilding", argsList.makeFunctionArgs());
}


void CvDLLWidgetData::doPediaBack()
{
	gDLL->getPythonIFace()->callFunction(PYScreensModule, "pediaBack");	
}

void CvDLLWidgetData::doPediaForward()
{
	gDLL->getPythonIFace()->callFunction(PYScreensModule, "pediaForward");	
}

void CvDLLWidgetData::doPediaBonusJump(CvWidgetDataStruct &widgetDataStruct, bool bData2)
{
	CyArgsList argsList;
	if (bData2)
	{
		argsList.add(widgetDataStruct.m_iData2);
	}
	else
	{
		argsList.add(widgetDataStruct.m_iData1);
	}
	gDLL->getPythonIFace()->callFunction(PYScreensModule, "pediaJumpToBonus", argsList.makeFunctionArgs());	
}

void CvDLLWidgetData::doPediaSpecialistJump(CvWidgetDataStruct &widgetDataStruct)
{
	CyArgsList argsList;
	argsList.add(widgetDataStruct.m_iData1);
	gDLL->getPythonIFace()->callFunction(PYScreensModule, "pediaJumpToSpecialist", argsList.makeFunctionArgs());	
}

void CvDLLWidgetData::doPediaMain(CvWidgetDataStruct &widgetDataStruct)
{
	CyArgsList argsList;
	argsList.add(widgetDataStruct.m_iData1 < 0 ? 0 : widgetDataStruct.m_iData1);
	gDLL->getPythonIFace()->callFunction(PYScreensModule, "pediaMain", argsList.makeFunctionArgs());	
}

void CvDLLWidgetData::doPediaPromotionJump(CvWidgetDataStruct &widgetDataStruct)
{
	CyArgsList argsList;
	argsList.add(widgetDataStruct.m_iData1);
	gDLL->getPythonIFace()->callFunction(PYScreensModule, "pediaJumpToPromotion", argsList.makeFunctionArgs());
}

void CvDLLWidgetData::doPediaUnitCombatJump(CvWidgetDataStruct &widgetDataStruct)
{
	CyArgsList argsList;
	argsList.add(widgetDataStruct.m_iData1);
	gDLL->getPythonIFace()->callFunction(PYScreensModule, "pediaJumpToUnitChart", argsList.makeFunctionArgs());
}

void CvDLLWidgetData::doPediaImprovementJump(CvWidgetDataStruct &widgetDataStruct, bool bData2)
{
	CyArgsList argsList;
	if (bData2)
	{
		argsList.add(widgetDataStruct.m_iData2);
	}
	else
	{
		argsList.add(widgetDataStruct.m_iData1);
	}
	gDLL->getPythonIFace()->callFunction(PYScreensModule, "pediaJumpToImprovement", argsList.makeFunctionArgs());
}

void CvDLLWidgetData::doPediaCivicJump(CvWidgetDataStruct &widgetDataStruct)
{
	CyArgsList argsList;
	argsList.add(widgetDataStruct.m_iData1);
	gDLL->getPythonIFace()->callFunction(PYScreensModule, "pediaJumpToCivic", argsList.makeFunctionArgs());
}

void CvDLLWidgetData::doPediaCivilizationJump(CvWidgetDataStruct &widgetDataStruct)
{
	CyArgsList argsList;
	argsList.add(widgetDataStruct.m_iData1);
	gDLL->getPythonIFace()->callFunction(PYScreensModule, "pediaJumpToCiv", argsList.makeFunctionArgs());
}

void CvDLLWidgetData::doPediaLeaderJump(CvWidgetDataStruct &widgetDataStruct)
{
	CyArgsList argsList;
	argsList.add(widgetDataStruct.m_iData1);
	gDLL->getPythonIFace()->callFunction(PYScreensModule, "pediaJumpToLeader", argsList.makeFunctionArgs());
}

void CvDLLWidgetData::doPediaDescription(CvWidgetDataStruct &widgetDataStruct)
{
	CyArgsList argsList;
	argsList.add(widgetDataStruct.m_iData1);
	argsList.add(widgetDataStruct.m_iData2);
	gDLL->getPythonIFace()->callFunction(PYScreensModule, "pediaShowHistorical", argsList.makeFunctionArgs());
}

void CvDLLWidgetData::doPediaBuildJump(CvWidgetDataStruct &widgetDataStruct)
{
	CyArgsList argsList;

	ImprovementTypes eImprovement = NO_IMPROVEMENT;
	BuildTypes eBuild = (BuildTypes)widgetDataStruct.m_iData2;
	if (NO_BUILD != eBuild)
	{
		eImprovement = (ImprovementTypes)GC.getBuildInfo(eBuild).getImprovement();
	}

	if (NO_IMPROVEMENT != eImprovement)
	{
		argsList.add(eImprovement);
		gDLL->getPythonIFace()->callFunction(PYScreensModule, "pediaJumpToImprovement", argsList.makeFunctionArgs());
	}
}

void CvDLLWidgetData::doGotoTurnEvent(CvWidgetDataStruct &widgetDataStruct)
{
	CvPlot* pPlot = GC.getMapINLINE().plotINLINE(widgetDataStruct.m_iData1, widgetDataStruct.m_iData2);

	if (NULL != pPlot && !gDLL->getEngineIFace()->isCameraLocked())
	{
		if (pPlot->isRevealed(GC.getGameINLINE().getActiveTeam(), false))
		{
			gDLL->getEngineIFace()->cameraLookAt(pPlot->getPoint());
		}
	}
}

void CvDLLWidgetData::doMenu( void )
{
	if (!gDLL->isGameInitializing())
	{
		CvPopupInfo* pInfo = new CvPopupInfo(BUTTONPOPUP_MAIN_MENU);
		if (NULL != pInfo)
		{
			gDLL->getInterfaceIFace()->addPopup(pInfo, NO_PLAYER, true);
		}
	}
}

void CvDLLWidgetData::doLaunch(CvWidgetDataStruct &widgetDataStruct)
{
	if (GET_TEAM(GC.getGameINLINE().getActiveTeam()).canLaunch((VictoryTypes)widgetDataStruct.m_iData1) && GC.getGameINLINE().testVictory((VictoryTypes)widgetDataStruct.m_iData1, GC.getGameINLINE().getActiveTeam()))
	{
		CvPopupInfo* pInfo = new CvPopupInfo(BUTTONPOPUP_LAUNCH, widgetDataStruct.m_iData1);
		if (NULL != pInfo)
		{
			gDLL->getInterfaceIFace()->addPopup(pInfo);
		}
	}
}

void CvDLLWidgetData::doForeignAdvisor(CvWidgetDataStruct &widgetDataStruct)
{
	CyArgsList argsList;
	argsList.add(widgetDataStruct.m_iData1);
	gDLL->getPythonIFace()->callFunction(PYScreensModule, "showForeignAdvisorScreen", argsList.makeFunctionArgs());
}

//
//	HELP PARSING FUNCTIONS
//

void CvDLLWidgetData::parsePlotListHelp(CvWidgetDataStruct &widgetDataStruct, CvWStringBuffer &szBuffer)
{
	PROFILE_FUNC();

	CvUnit* pUnit;

	int iUnitIndex = widgetDataStruct.m_iData1 + gDLL->getInterfaceIFace()->getPlotListColumn() - gDLL->getInterfaceIFace()->getPlotListOffset();

	CvPlot *selectionPlot = gDLL->getInterfaceIFace()->getSelectionPlot();
	pUnit = gDLL->getInterfaceIFace()->getInterfacePlotUnit(selectionPlot, iUnitIndex);

	if (pUnit != NULL)
	{
		GAMETEXT.setUnitHelp(szBuffer, pUnit);

		if (pUnit->plot()->plotCount(PUF_isUnitType, pUnit->getUnitType(), -1, pUnit->getOwnerINLINE()) > 1)
		{
			szBuffer.append(NEWLINE);
			szBuffer.append(gDLL->getText("TXT_KEY_MISC_CTRL_SELECT", GC.getUnitInfo(pUnit->getUnitType()).getTextKeyWide()));
		}

		if (pUnit->plot()->plotCount(NULL, -1, -1, pUnit->getOwnerINLINE()) > 1)
		{
			szBuffer.append(NEWLINE);
			szBuffer.append(gDLL->getText("TXT_KEY_MISC_ALT_SELECT"));
		}
	}
}


void CvDLLWidgetData::parseLiberateCityHelp(CvWidgetDataStruct &widgetDataStruct, CvWStringBuffer &szBuffer)
{
	CvCity* pHeadSelectedCity;
	CvWString szTempBuffer;

	pHeadSelectedCity = gDLL->getInterfaceIFace()->getHeadSelectedCity();

	if (pHeadSelectedCity != NULL)
	{
		PlayerTypes ePlayer = pHeadSelectedCity->getLiberationPlayer(false);
		if (NO_PLAYER != ePlayer)
		{
			szBuffer.append(gDLL->getText("TXT_KEY_LIBERATE_CITY_HELP", pHeadSelectedCity->getNameKey(), GET_PLAYER(ePlayer).getNameKey()));
		}
	}
}

void CvDLLWidgetData::parseCityNameHelp(CvWidgetDataStruct &widgetDataStruct, CvWStringBuffer &szBuffer)
{
	CvCity* pHeadSelectedCity;
	CvWString szTempBuffer;

	pHeadSelectedCity = gDLL->getInterfaceIFace()->getHeadSelectedCity();

	if (pHeadSelectedCity != NULL)
	{
		szBuffer.append(pHeadSelectedCity->getName());

		szBuffer.append(NEWLINE);
		szBuffer.append(gDLL->getText("TXT_KEY_CITY_POPULATION", pHeadSelectedCity->getRealPopulation()));

		GAMETEXT.setTimeStr(szTempBuffer, pHeadSelectedCity->getGameTurnFounded(), false);
		szBuffer.append(NEWLINE);
		szBuffer.append(gDLL->getText("TXT_KEY_CITY_FOUNDED", szTempBuffer.GetCString()));

		szBuffer.append(NEWLINE);
		szBuffer.append(gDLL->getText("TXT_KEY_CHANGE_NAME"));
	}
}



void CvDLLWidgetData::parseTrainHelp(CvWidgetDataStruct &widgetDataStruct, CvWStringBuffer &szBuffer)
{
	CvCity* pHeadSelectedCity;
	UnitTypes eUnit;

	if (widgetDataStruct.m_iData2 != FFreeList::INVALID_INDEX)
	{
		pHeadSelectedCity = GET_PLAYER(GC.getGameINLINE().getActivePlayer()).getCity(widgetDataStruct.m_iData2);
	}
	else
	{
		pHeadSelectedCity = gDLL->getInterfaceIFace()->getHeadSelectedCity();
	}

	if (pHeadSelectedCity != NULL)
	{
		eUnit = (UnitTypes)GC.getCivilizationInfo(pHeadSelectedCity->getCivilizationType()).getCivilizationUnits(widgetDataStruct.m_iData1);

		GAMETEXT.setUnitHelp(szBuffer, eUnit, false, widgetDataStruct.m_bOption, false, pHeadSelectedCity);
	}
}


void CvDLLWidgetData::parseConstructHelp(CvWidgetDataStruct &widgetDataStruct, CvWStringBuffer &szBuffer)
{
	CvCity* pHeadSelectedCity;
	BuildingTypes eBuilding;

	if (widgetDataStruct.m_iData2 != FFreeList::INVALID_INDEX)
	{
		pHeadSelectedCity = GET_PLAYER(GC.getGameINLINE().getActivePlayer()).getCity(widgetDataStruct.m_iData2);
	}
	else
	{
		pHeadSelectedCity = gDLL->getInterfaceIFace()->getHeadSelectedCity();
	}

	if (pHeadSelectedCity != NULL)
	{
		eBuilding = (BuildingTypes)GC.getCivilizationInfo(pHeadSelectedCity->getCivilizationType()).getCivilizationBuildings(widgetDataStruct.m_iData1);

		GAMETEXT.setBuildingHelp(szBuffer, eBuilding, false, widgetDataStruct.m_bOption, false, pHeadSelectedCity);
	}
}


void CvDLLWidgetData::parseCreateHelp(CvWidgetDataStruct &widgetDataStruct, CvWStringBuffer &szBuffer)
{
	CvCity* pHeadSelectedCity;

	if (widgetDataStruct.m_iData2 != FFreeList::INVALID_INDEX)
	{
		pHeadSelectedCity = GET_PLAYER(GC.getGameINLINE().getActivePlayer()).getCity(widgetDataStruct.m_iData2);
	}
	else
	{
		pHeadSelectedCity = gDLL->getInterfaceIFace()->getHeadSelectedCity();
	}

	GAMETEXT.setProjectHelp(szBuffer, ((ProjectTypes)widgetDataStruct.m_iData1), false, pHeadSelectedCity);
}


void CvDLLWidgetData::parseMaintainHelp(CvWidgetDataStruct &widgetDataStruct, CvWStringBuffer &szBuffer)
{
	GAMETEXT.setProcessHelp(szBuffer, ((ProcessTypes)(widgetDataStruct.m_iData1)));
}


void CvDLLWidgetData::parseHurryHelp(CvWidgetDataStruct &widgetDataStruct, CvWStringBuffer &szBuffer)
{
	CvCity* pHeadSelectedCity;
	CvWString szTempBuffer;
	bool bFirst;
	int iHurryGold;
	int iHurryPopulation;
	int iHurryAngerLength;
	int iI;

	pHeadSelectedCity = gDLL->getInterfaceIFace()->getHeadSelectedCity();

	if (pHeadSelectedCity != NULL)
	{
		szBuffer.assign(gDLL->getText("TXT_KEY_MISC_HURRY_PROD", pHeadSelectedCity->getProductionNameKey()));

		iHurryGold = pHeadSelectedCity->hurryGold((HurryTypes)(widgetDataStruct.m_iData1));

		if (iHurryGold > 0)
		{
			szBuffer.append(NEWLINE);
			szBuffer.append(gDLL->getText("TXT_KEY_MISC_HURRY_GOLD", iHurryGold));
		}

		iHurryPopulation = pHeadSelectedCity->hurryPopulation((HurryTypes)(widgetDataStruct.m_iData1));

		if (iHurryPopulation > 0)
		{
			szBuffer.append(NEWLINE);
			szBuffer.append(gDLL->getText("TXT_KEY_MISC_HURRY_POP", iHurryPopulation));

			if (iHurryPopulation > pHeadSelectedCity->maxHurryPopulation())
			{
				szBuffer.append(gDLL->getText("TXT_KEY_MISC_MAX_POP_HURRY", pHeadSelectedCity->maxHurryPopulation()));
			}
		}

		iHurryAngerLength = pHeadSelectedCity->hurryAngerLength((HurryTypes)(widgetDataStruct.m_iData1));

		if (iHurryAngerLength > 0)
		{
			szBuffer.append(NEWLINE);
			szBuffer.append(gDLL->getText("TXT_KEY_MISC_ANGER_TURNS", GC.getDefineINT("HURRY_POP_ANGER"), (iHurryAngerLength + pHeadSelectedCity->getHurryAngerTimer())));
		}

		if (!(pHeadSelectedCity->isProductionUnit()) && !(pHeadSelectedCity->isProductionBuilding()))
		{
			szBuffer.append(NEWLINE);
			szBuffer.append(gDLL->getText("TXT_KEY_MISC_UNIT_BUILDING_HURRY"));
		}

		if (!(GET_PLAYER(pHeadSelectedCity->getOwnerINLINE()).canHurry((HurryTypes)(widgetDataStruct.m_iData1))))
		{
			bFirst = true;

			for (iI = 0; iI < GC.getNumCivicInfos(); iI++)
			{
				if (GC.getCivicInfo((CivicTypes)iI).isHurry(widgetDataStruct.m_iData1))
				{
					szTempBuffer = NEWLINE + gDLL->getText("TXT_KEY_REQUIRES");
					setListHelp(szBuffer, szTempBuffer, GC.getCivicInfo((CivicTypes)iI).getDescription(), gDLL->getText("TXT_KEY_OR").c_str(), bFirst);
					bFirst = false;
				}
			}		

			if (!bFirst)
			{
				szBuffer.append(ENDCOLR);
			}
		}
	}
}


void CvDLLWidgetData::parseConscriptHelp(CvWidgetDataStruct &widgetDataStruct, CvWStringBuffer &szBuffer)
{
	CvCity* pHeadSelectedCity;
	CvWString szTempBuffer;
	int iConscriptPopulation;
	int iConscriptAngerLength;
	int iMinCityPopulation;
	int iMinCulturePercent;
	int iI;
	bool bFirst;

	pHeadSelectedCity = gDLL->getInterfaceIFace()->getHeadSelectedCity();

	if (pHeadSelectedCity != NULL)
	{
		if (pHeadSelectedCity->getConscriptUnit() != NO_UNIT)
		{
			CvWString szTemp;
			szTemp.Format(SETCOLR L"%s" ENDCOLR, TEXT_COLOR("COLOR_UNIT_TEXT"), GC.getUnitInfo(pHeadSelectedCity->getConscriptUnit()).getDescription());
			szBuffer.assign(szTemp);

			iConscriptPopulation = pHeadSelectedCity->getConscriptPopulation();

			if (iConscriptPopulation > 0)
			{
				szBuffer.append(NEWLINE);
				szBuffer.append(gDLL->getText("TXT_KEY_MISC_HURRY_POP", iConscriptPopulation));
			}

			iConscriptAngerLength = pHeadSelectedCity->flatConscriptAngerLength();

			if (iConscriptAngerLength > 0)
			{
				szBuffer.append(NEWLINE);
				szBuffer.append(gDLL->getText("TXT_KEY_MISC_ANGER_TURNS", GC.getDefineINT("CONSCRIPT_POP_ANGER"), (iConscriptAngerLength + pHeadSelectedCity->getConscriptAngerTimer())));
			}

			iMinCityPopulation = pHeadSelectedCity->conscriptMinCityPopulation();

			if (pHeadSelectedCity->getPopulation() < iMinCityPopulation)
			{
				szBuffer.append(NEWLINE);
				szBuffer.append(gDLL->getText("TXT_KEY_MISC_MIN_CITY_POP", iMinCityPopulation));
			}

			iMinCulturePercent = GC.getDefineINT("CONSCRIPT_MIN_CULTURE_PERCENT");

			if (pHeadSelectedCity->plot()->calculateTeamCulturePercent(pHeadSelectedCity->getTeam()) < iMinCulturePercent)
			{
				szBuffer.append(NEWLINE);
				szBuffer.append(gDLL->getText("TXT_KEY_MISC_MIN_CULTURE_PERCENT", iMinCulturePercent));
			}

			if (GET_PLAYER(pHeadSelectedCity->getOwnerINLINE()).getMaxConscript() == 0)
			{
				bFirst = true;

				for (iI = 0; iI < GC.getNumCivicInfos(); iI++)
				{
					if (getWorldSizeMaxConscript((CivicTypes)iI) > 0)
					{
						szTempBuffer = NEWLINE + gDLL->getText("TXT_KEY_REQUIRES");
						setListHelp(szBuffer, szTempBuffer, GC.getCivicInfo((CivicTypes)iI).getDescription(), gDLL->getText("TXT_KEY_OR").c_str(), bFirst);
						bFirst = false;
					}
				}		

				if (!bFirst)
				{
					szBuffer.append(ENDCOLR);
				}
			}
		}
	}
}


void CvDLLWidgetData::parseActionHelp(CvWidgetDataStruct &widgetDataStruct, CvWStringBuffer &szBuffer)
{
	CLLNode<IDInfo>* pSelectedUnitNode;
	CvCity* pMissionCity;
	CvCity* pCity;
	CvUnit* pHeadSelectedUnit;
	CvUnit* pSelectedUnit;
	CvPlot* pMissionPlot;
	CvPlot* pLoopPlot;
	CvWString szTempBuffer;
	CvWString szFirstBuffer;
	ImprovementTypes eImprovement;
	ImprovementTypes eFinalImprovement;
	ReligionTypes eReligion;
	BuildingTypes eBuilding;
	PlayerTypes eGiftPlayer;
	BuildTypes eBuild;
	RouteTypes eRoute;
	BonusTypes eBonus;
	TechTypes eTech;
	bool bAlt;
	bool bShift;
	bool bValid;
	int iYield;
	int iUnitConsume;
	int iUnitDiff;
	int iProduction;
	int iMovementCost;
	int iFlatMovementCost;
	int iMoves;
	int iFlatMoves;
	int iNowWorkRate;
	int iThenWorkRate;
	int iTurns;
	int iPrice;
	int iLow;
	int iHigh;
	int iLast;
	int iRange;
	int iDX, iDY;
	int iI;

	bAlt = gDLL->altKey();
	bShift = gDLL->shiftKey();

	CvWString szTemp;
	szTemp.Format(SETCOLR L"%s" ENDCOLR , TEXT_COLOR("COLOR_HIGHLIGHT_TEXT"), GC.getActionInfo(widgetDataStruct.m_iData1).getHotKeyDescription().c_str());
	szBuffer.assign(szTemp);

	pHeadSelectedUnit = gDLL->getInterfaceIFace()->getHeadSelectedUnit();

	if (pHeadSelectedUnit != NULL)
	{
		if (GC.getActionInfo(widgetDataStruct.m_iData1).getMissionType() != NO_MISSION)
		{
			if (bShift && gDLL->getInterfaceIFace()->mirrorsSelectionGroup())
			{
				pMissionPlot = pHeadSelectedUnit->getGroup()->lastMissionPlot();
			}
			else
			{
				pMissionPlot = pHeadSelectedUnit->plot();
			}

			pMissionCity = pMissionPlot->getPlotCity();

			if (GC.getActionInfo(widgetDataStruct.m_iData1).getMissionType() == MISSION_HEAL)
			{
				iTurns = 0;

				pSelectedUnitNode = gDLL->getInterfaceIFace()->headSelectionListNode();

				while (pSelectedUnitNode != NULL)
				{
					pSelectedUnit = ::getUnit(pSelectedUnitNode->m_data);
					iTurns = std::max(iTurns, pSelectedUnit->healTurns(pMissionPlot));

					pSelectedUnitNode = gDLL->getInterfaceIFace()->nextSelectionListNode(pSelectedUnitNode);
				}

				szBuffer.append(NEWLINE);
				szBuffer.append(gDLL->getText("TXT_KEY_MISC_TURN_OR_TURNS", iTurns));
			}
			else if (GC.getActionInfo(widgetDataStruct.m_iData1).getMissionType() == MISSION_PILLAGE)
			{
				if (pMissionPlot->getImprovementType() != NO_IMPROVEMENT)
				{
					szBuffer.append(NEWLINE);
					szBuffer.append(gDLL->getText("TXT_KEY_ACTION_DESTROY_IMP", GC.getImprovementInfo(pMissionPlot->getImprovementType()).getTextKeyWide()));
				}
				else if (pMissionPlot->getRouteType() != NO_ROUTE)
				{
					szBuffer.append(NEWLINE);
					szBuffer.append(gDLL->getText("TXT_KEY_ACTION_DESTROY_IMP", GC.getRouteInfo(pMissionPlot->getRouteType()).getTextKeyWide()));
				}
			}
			else if (GC.getActionInfo(widgetDataStruct.m_iData1).getMissionType() == MISSION_PLUNDER)
			{
				pMissionPlot = pHeadSelectedUnit->plot();

				if (pMissionPlot->getTeam() == pHeadSelectedUnit->getTeam())
				{
					szBuffer.append(NEWLINE);
					szBuffer.append(gDLL->getText("TXT_KEY_ACTION_PLUNDER_IN_BORDERS"));
				}
			}
			else if (GC.getActionInfo(widgetDataStruct.m_iData1).getMissionType() == MISSION_SABOTAGE)
			{
				pSelectedUnitNode = gDLL->getInterfaceIFace()->headSelectionListNode();

				while (pSelectedUnitNode != NULL)
				{
					pSelectedUnit = ::getUnit(pSelectedUnitNode->m_data);

					if (pSelectedUnit->canSabotage(pMissionPlot, true)) // XXX if queuing up this action, use the current plot along the goto...
					{
						iPrice = pSelectedUnit->sabotageCost(pMissionPlot);
						if (iPrice > 0)
						{
							szTempBuffer.Format(L"%d %c", iPrice, GC.getCommerceInfo(COMMERCE_GOLD).getChar());
							szBuffer.append(NEWLINE);
							szBuffer.append(szTempBuffer);
						}

						iLow = pSelectedUnit->sabotageProb(pMissionPlot, PROBABILITY_LOW);
						iHigh = pSelectedUnit->sabotageProb(pMissionPlot, PROBABILITY_HIGH);

						if (iLow == iHigh)
						{
							szBuffer.append(NEWLINE);
							szBuffer.append(gDLL->getText("TXT_KEY_ACTION_PROBABILITY", iHigh));
						}
						else
						{
							szBuffer.append(NEWLINE);
							szBuffer.append(gDLL->getText("TXT_KEY_ACTION_PROBABILITY_RANGE", iLow, iHigh));
						}
						break;
					}

					pSelectedUnitNode = gDLL->getInterfaceIFace()->nextSelectionListNode(pSelectedUnitNode);
				}
			}
			else if (GC.getActionInfo(widgetDataStruct.m_iData1).getMissionType() == MISSION_DESTROY)
			{
				pSelectedUnitNode = gDLL->getInterfaceIFace()->headSelectionListNode();

				while (pSelectedUnitNode != NULL)
				{
					pSelectedUnit = ::getUnit(pSelectedUnitNode->m_data);

					if (pSelectedUnit->canDestroy(pMissionPlot, true)) // XXX if queuing up this action, use the current plot along the goto...
					{
						iPrice = pSelectedUnit->destroyCost(pMissionPlot);
						if (iPrice > 0)
						{
							szTempBuffer.Format(L"%d %c", iPrice, GC.getCommerceInfo(COMMERCE_GOLD).getChar());
							szBuffer.append(NEWLINE);
							szBuffer.append(szTempBuffer);
						}

						iLow = pSelectedUnit->destroyProb(pMissionPlot, PROBABILITY_LOW);
						iHigh = pSelectedUnit->destroyProb(pMissionPlot, PROBABILITY_HIGH);

						if (iLow == iHigh)
						{
							szBuffer.append(NEWLINE);
							szBuffer.append(gDLL->getText("TXT_KEY_ACTION_PROBABILITY", iHigh));
						}
						else
						{
							szBuffer.append(NEWLINE);
							szBuffer.append(gDLL->getText("TXT_KEY_ACTION_PROBABILITY_RANGE", iLow, iHigh));
						}
						break;
					}

					pSelectedUnitNode = gDLL->getInterfaceIFace()->nextSelectionListNode(pSelectedUnitNode);
				}
			}
			else if (GC.getActionInfo(widgetDataStruct.m_iData1).getMissionType() == MISSION_STEAL_PLANS)
			{
				pSelectedUnitNode = gDLL->getInterfaceIFace()->headSelectionListNode();

				while (pSelectedUnitNode != NULL)
				{
					pSelectedUnit = ::getUnit(pSelectedUnitNode->m_data);

					if (pSelectedUnit->canStealPlans(pMissionPlot, true)) // XXX if queuing up this action, use the current plot along the goto...
					{
						iPrice = pSelectedUnit->stealPlansCost(pMissionPlot);
						if (iPrice > 0)
						{
							szTempBuffer.Format(L"%d %c", iPrice, GC.getCommerceInfo(COMMERCE_GOLD).getChar());
							szBuffer.append(NEWLINE);
							szBuffer.append(szTempBuffer);
						}

						iLow = pSelectedUnit->stealPlansProb(pMissionPlot, PROBABILITY_LOW);
						iHigh = pSelectedUnit->stealPlansProb(pMissionPlot, PROBABILITY_HIGH);

						if (iLow == iHigh)
						{
							szBuffer.append(NEWLINE);
							szBuffer.append(gDLL->getText("TXT_KEY_ACTION_PROBABILITY", iHigh));
						}
						else
						{
							szBuffer.append(NEWLINE);
							szBuffer.append(gDLL->getText("TXT_KEY_ACTION_PROBABILITY_RANGE", iLow, iHigh));
						}
						break;
					}

					pSelectedUnitNode = gDLL->getInterfaceIFace()->nextSelectionListNode(pSelectedUnitNode);
				}
			}
			else if (GC.getActionInfo(widgetDataStruct.m_iData1).getMissionType() == MISSION_FOUND)
			{
				if (!(GET_PLAYER(pHeadSelectedUnit->getOwnerINLINE()).canFound(pMissionPlot->getX_INLINE(), pMissionPlot->getY_INLINE())))
				{
					bValid = true;

					iRange = GC.getMIN_CITY_RANGE();

					for (iDX = -(iRange); iDX <= iRange; iDX++)
					{
						for (iDY = -(iRange); iDY <= iRange; iDY++)
						{
							pLoopPlot	= plotXY(pMissionPlot->getX_INLINE(), pMissionPlot->getY_INLINE(), iDX, iDY);

							if (pLoopPlot != NULL)
							{
								if (pLoopPlot->isCity())
								{
									bValid = false;
								}
							}
						}
					}

					if (!bValid)
					{
						szBuffer.append(NEWLINE);
						szBuffer.append(gDLL->getText("TXT_KEY_ACTION_CANNOT_FOUND", GC.getMIN_CITY_RANGE()));
					}
				}
			}
			else if (GC.getActionInfo(widgetDataStruct.m_iData1).getMissionType() == MISSION_SPREAD)
			{
				eReligion = ((ReligionTypes)(GC.getActionInfo(widgetDataStruct.m_iData1).getMissionData()));

				if (pMissionCity != NULL)
				{
					if (pMissionCity->getTeam() != pHeadSelectedUnit->getTeam()) // XXX still true???
					{
						if (GET_PLAYER(pMissionCity->getOwnerINLINE()).isNoNonStateReligionSpread())
						{
							if (eReligion != GET_PLAYER(pMissionCity->getOwnerINLINE()).getStateReligion())
							{
								szBuffer.append(NEWLINE);
								szBuffer.append(gDLL->getText("TXT_KEY_ACTION_CANNOT_SPREAD_NON_STATE_RELIGION"));
							}
						}
					}

					szBuffer.append(NEWLINE);
					GAMETEXT.setReligionHelpCity(szBuffer, eReligion, pMissionCity, false, true);
				}
			}
			else if (GC.getActionInfo(widgetDataStruct.m_iData1).getMissionType() == MISSION_SPREAD_CORPORATION)
			{
				CorporationTypes eCorporation = ((CorporationTypes)(GC.getActionInfo(widgetDataStruct.m_iData1).getMissionData()));

				if (pMissionCity != NULL)
				{
					szBuffer.append(NEWLINE);
					GAMETEXT.setCorporationHelpCity(szBuffer, eCorporation, pMissionCity, false, true);

					for (int iCorp = 0; iCorp < GC.getNumCorporationInfos(); ++iCorp)
					{
						if (eCorporation != iCorp)
						{
							if (pMissionCity->isHasCorporation((CorporationTypes)iCorp))
							{
								if (GC.getGameINLINE().isCompetingCorporation(eCorporation, (CorporationTypes)iCorp))
								{
									szBuffer.append(NEWLINE);
									szBuffer.append(gDLL->getText("TXT_KEY_ACTION_WILL_ELIMINATE_CORPORATION", GC.getCorporationInfo((CorporationTypes)iCorp).getTextKeyWide()));
								}
							}
						}
					}

					szTempBuffer.Format(L"%s%d %c", NEWLINE, pHeadSelectedUnit->spreadCorporationCost(eCorporation, pMissionCity), GC.getCommerceInfo(COMMERCE_GOLD).getChar());
					szBuffer.append(szTempBuffer);

					if (!pHeadSelectedUnit->canSpreadCorporation(pMissionPlot, eCorporation))
					{
						if (!GET_PLAYER(pMissionCity->getOwnerINLINE()).isActiveCorporation(eCorporation))
						{
							szBuffer.append(NEWLINE);
							szBuffer.append(gDLL->getText("TXT_KEY_ACTION_CORPORATION_NOT_ACTIVE", GC.getCorporationInfo(eCorporation).getTextKeyWide(), GET_PLAYER(pMissionCity->getOwnerINLINE()).getCivilizationAdjective()));
						}

						CorporationTypes eCompetition = NO_CORPORATION;
						for (int iCorporation = 0; iCorporation < GC.getNumCorporationInfos(); ++iCorporation)
						{
							if (pMissionCity->isHeadquarters((CorporationTypes)iCorporation))
							{
								if (GC.getGameINLINE().isCompetingCorporation((CorporationTypes)iCorporation, eCorporation))
								{
									eCompetition = (CorporationTypes)iCorporation;
									break;
								}
							}
						}

						if (NO_CORPORATION != eCompetition)
						{
							szBuffer.append(NEWLINE);
							szBuffer.append(gDLL->getText("TXT_KEY_ACTION_CORPORATION_COMPETING_HEADQUARTERS", GC.getCorporationInfo(eCorporation).getTextKeyWide(), GC.getCorporationInfo(eCompetition).getTextKeyWide()));
						}

						CvWStringBuffer szBonusList;
						bool bValid = false;
						bool bFirst = true;
						for (int i = 0; i < GC.getNUM_CORPORATION_PREREQ_BONUSES(); ++i)
						{
							BonusTypes eBonus = (BonusTypes)GC.getCorporationInfo(eCorporation).getPrereqBonus(i);
							if (NO_BONUS != eBonus)
							{
								if (!bFirst)
								{
									szBonusList.append(L", ");
								}
								else
								{
									bFirst = false;
								}
								szBonusList.append(GC.getBonusInfo(eBonus).getDescription());

								if (pMissionCity->hasBonus(eBonus))
								{
									bValid = true;
									break;
								}
							}
						}

						if (!bValid)
						{
							szBuffer.append(NEWLINE);
							szBuffer.append(gDLL->getText("TXT_KEY_ACTION_CORPORATION_NO_RESOURCES", pMissionCity->getNameKey(), szBonusList.getCString()));
						}
					}
				}
			}
			else if (GC.getActionInfo(widgetDataStruct.m_iData1).getMissionType() == MISSION_JOIN)
			{
				GAMETEXT.parseSpecialistHelp(szBuffer, ((SpecialistTypes)(GC.getActionInfo(widgetDataStruct.m_iData1).getMissionData())), pMissionCity, true);
			}
			else if (GC.getActionInfo(widgetDataStruct.m_iData1).getMissionType() == MISSION_CONSTRUCT)
			{
				eBuilding = ((BuildingTypes)(GC.getActionInfo(widgetDataStruct.m_iData1).getMissionData()));

				if (pMissionCity != NULL)
				{
					if (!pHeadSelectedUnit->getUnitInfo().getForceBuildings(eBuilding)  && !pMissionCity->canConstruct(eBuilding, false, false, true))
					{
						if (!(GC.getGameINLINE().isBuildingClassMaxedOut((BuildingClassTypes)(GC.getBuildingInfo(eBuilding).getBuildingClassType()))))
						{
							GAMETEXT.buildBuildingRequiresString(szBuffer, ((BuildingTypes)(GC.getActionInfo(widgetDataStruct.m_iData1).getMissionData())), false, false, pMissionCity);
						}
					}
					else
					{
						szBuffer.append(NEWLINE);
						GAMETEXT.setBuildingHelp(szBuffer, ((BuildingTypes)(GC.getActionInfo(widgetDataStruct.m_iData1).getMissionData())), false, false, false, pMissionCity);
					}
				}
			}
			else if (GC.getActionInfo(widgetDataStruct.m_iData1).getMissionType() == MISSION_DISCOVER)
			{
				pSelectedUnitNode = gDLL->getInterfaceIFace()->headSelectionListNode();

				while (pSelectedUnitNode != NULL)
				{
					pSelectedUnit = ::getUnit(pSelectedUnitNode->m_data);

					if (pSelectedUnit->canDiscover(pMissionPlot))
					{
						eTech = pSelectedUnit->getDiscoveryTech();
	
						if (pSelectedUnit->getDiscoverResearch(eTech) >= GET_TEAM(pSelectedUnit->getTeam()).getResearchLeft(eTech))
						{
							szTempBuffer.Format(SETCOLR L"%s" ENDCOLR, TEXT_COLOR("COLOR_TECH_TEXT"), GC.getTechInfo(eTech).getDescription());
							szBuffer.append(NEWLINE);
							szBuffer.append(szTempBuffer);
						}
						else
						{
							szBuffer.append(NEWLINE);
							szBuffer.append(gDLL->getText("TXT_KEY_ACTION_EXTRA_RESEARCH", pSelectedUnit->getDiscoverResearch(eTech), GC.getTechInfo(eTech).getTextKeyWide()));
						}
						break;
					}

					pSelectedUnitNode = gDLL->getInterfaceIFace()->nextSelectionListNode(pSelectedUnitNode);
				}
			}
			else if (GC.getActionInfo(widgetDataStruct.m_iData1).getMissionType() == MISSION_HURRY)
			{
				if (pMissionCity != NULL)
				{
					if (!(pMissionCity->isProductionBuilding()))
					{
						szBuffer.append(NEWLINE);
						szBuffer.append(gDLL->getText("TXT_KEY_ACTION_BUILDING_HURRY"));
					}
					else
					{
						pSelectedUnitNode = gDLL->getInterfaceIFace()->headSelectionListNode();

						while (pSelectedUnitNode != NULL)
						{
							pSelectedUnit = ::getUnit(pSelectedUnitNode->m_data);

							if (pSelectedUnit->canHurry(pMissionPlot, true))
							{
								const wchar* pcKey = NULL;
								if (NO_PROJECT != pMissionCity->getProductionProject())
								{
									pcKey = GC.getProjectInfo(pMissionCity->getProductionProject()).getTextKeyWide();
								}
								else if (NO_BUILDING != pMissionCity->getProductionBuilding())
								{
									pcKey = GC.getBuildingInfo(pMissionCity->getProductionBuilding()).getTextKeyWide();
								}
								else if (NO_UNIT != pMissionCity->getProductionUnit())
								{
									pcKey = GC.getUnitInfo(pMissionCity->getProductionUnit()).getTextKeyWide();
								}
								if (NULL != pcKey && pSelectedUnit->getHurryProduction(pMissionPlot) >= pMissionCity->productionLeft())
								{
									szBuffer.append(NEWLINE);
									szBuffer.append(gDLL->getText("TXT_KEY_ACTION_FINISH_CONSTRUCTION", pcKey));
								}
								else
								{
									szBuffer.append(NEWLINE);
									szBuffer.append(gDLL->getText("TXT_KEY_ACTION_EXTRA_CONSTRUCTION", pSelectedUnit->getHurryProduction(pMissionPlot), pcKey));
								}
								break;
							}

							pSelectedUnitNode = gDLL->getInterfaceIFace()->nextSelectionListNode(pSelectedUnitNode);
						}
					}
				}
			}
			else if (GC.getActionInfo(widgetDataStruct.m_iData1).getMissionType() == MISSION_TRADE)
			{
				if (pMissionCity != NULL)
				{
					if (pMissionCity->getOwnerINLINE() == pHeadSelectedUnit->getOwnerINLINE())
					{
						szBuffer.append(NEWLINE);
						szBuffer.append(gDLL->getText("TXT_KEY_ACTION_TRADE_MISSION_FOREIGN"));
					}
					else
					{
						pSelectedUnitNode = gDLL->getInterfaceIFace()->headSelectionListNode();

						while (pSelectedUnitNode != NULL)
						{
							pSelectedUnit = ::getUnit(pSelectedUnitNode->m_data);

							if (pSelectedUnit->canTrade(pMissionPlot, true))
							{
								szTempBuffer.Format(L"%s+%d%c", NEWLINE, pSelectedUnit->getTradeGold(pMissionPlot), GC.getCommerceInfo(COMMERCE_GOLD).getChar());
								szBuffer.append(szTempBuffer);
								break;
							}

							pSelectedUnitNode = gDLL->getInterfaceIFace()->nextSelectionListNode(pSelectedUnitNode);
						}
					}
				}
			}
			else if (GC.getActionInfo(widgetDataStruct.m_iData1).getMissionType() == MISSION_GREAT_WORK)
			{
				pSelectedUnitNode = gDLL->getInterfaceIFace()->headSelectionListNode();

				while (pSelectedUnitNode != NULL)
				{
					pSelectedUnit = ::getUnit(pSelectedUnitNode->m_data);

					if (pSelectedUnit->canGreatWork(pMissionPlot))
					{
						szTempBuffer.Format(L"%s+%d%c", NEWLINE, pSelectedUnit->getGreatWorkCulture(pMissionPlot), GC.getCommerceInfo(COMMERCE_CULTURE).getChar());
						szBuffer.append(szTempBuffer);
						break;
					}

					pSelectedUnitNode = gDLL->getInterfaceIFace()->nextSelectionListNode(pSelectedUnitNode);
				}
			}
			else if (GC.getActionInfo(widgetDataStruct.m_iData1).getMissionType() == MISSION_INFILTRATE)
			{
				if (pMissionCity != NULL)
				{
					if (pMissionCity->getOwnerINLINE() == pHeadSelectedUnit->getOwnerINLINE())
					{
						szBuffer.append(NEWLINE);
						szBuffer.append(gDLL->getText("TXT_KEY_ACTION_INFILTRATE_MISSION_FOREIGN"));
					}
					else
					{
						pSelectedUnitNode = gDLL->getInterfaceIFace()->headSelectionListNode();

						while (pSelectedUnitNode != NULL)
						{
							pSelectedUnit = ::getUnit(pSelectedUnitNode->m_data);

							if (pSelectedUnit->canEspionage(pMissionPlot))
							{
								szTempBuffer.Format(L"%s+%d%c", NEWLINE, pSelectedUnit->getEspionagePoints(pMissionPlot), GC.getCommerceInfo(COMMERCE_ESPIONAGE).getChar());
								szBuffer.append(szTempBuffer);
								break;
							}

							pSelectedUnitNode = gDLL->getInterfaceIFace()->nextSelectionListNode(pSelectedUnitNode);
						}
					}
				}
			}
			else if (GC.getActionInfo(widgetDataStruct.m_iData1).getMissionType() == MISSION_GOLDEN_AGE)
			{
				iUnitConsume = GET_PLAYER(pHeadSelectedUnit->getOwnerINLINE()).unitsRequiredForGoldenAge();
				iUnitDiff = (iUnitConsume - GET_PLAYER(pHeadSelectedUnit->getOwnerINLINE()).unitsGoldenAgeReady());

				if (iUnitDiff > 0)
				{
					szBuffer.append(NEWLINE);
					szBuffer.append(gDLL->getText("TXT_KEY_ACTION_MORE_GREAT_PEOPLE", iUnitDiff));
				}

				if (iUnitConsume > 1)
				{
					szBuffer.append(NEWLINE);
					szBuffer.append(gDLL->getText("TXT_KEY_ACTION_CONSUME_GREAT_PEOPLE", iUnitConsume));
				}
			}
			else if (GC.getActionInfo(widgetDataStruct.m_iData1).getMissionType() == MISSION_LEAD)
			{
				if (pHeadSelectedUnit->getUnitInfo().getLeaderExperience() > 0)
				{
					int iNumUnits = pHeadSelectedUnit->canGiveExperience(pHeadSelectedUnit->plot());
					if (iNumUnits > 0)
					{
						szBuffer.append(NEWLINE);
						szBuffer.append(gDLL->getText("TXT_KEY_ACTION_LEAD_TROOPS", pHeadSelectedUnit->getStackExperienceToGive(iNumUnits)));
					}
				}
				if (pHeadSelectedUnit->getUnitInfo().getLeaderPromotion() != NO_PROMOTION)
				{
					szBuffer.append(NEWLINE);
					szBuffer.append(gDLL->getText("TXT_KEY_PROMOTION_WHEN_LEADING"));
					GAMETEXT.parsePromotionHelp(szBuffer, (PromotionTypes)pHeadSelectedUnit->getUnitInfo().getLeaderPromotion(), L"\n   ");
				}
			}
			else if (GC.getActionInfo(widgetDataStruct.m_iData1).getMissionType() == MISSION_ESPIONAGE)
			{
				szBuffer.append(NEWLINE);
				szBuffer.append(gDLL->getText("TXT_KEY_ACTION_ESPIONAGE_MISSION"));

				GAMETEXT.setEspionageMissionHelp(szBuffer, pHeadSelectedUnit);
			}
			else if (GC.getActionInfo(widgetDataStruct.m_iData1).getMissionType() == MISSION_BUILD)
			{
				eBuild = ((BuildTypes)(GC.getActionInfo(widgetDataStruct.m_iData1).getMissionData()));
				FAssert(eBuild != NO_BUILD);
				eImprovement = ((ImprovementTypes)(GC.getBuildInfo(eBuild).getImprovement()));
				eRoute = ((RouteTypes)(GC.getBuildInfo(eBuild).getRoute()));
				eBonus = pMissionPlot->getBonusType(pHeadSelectedUnit->getTeam());

				for (iI = 0; iI < NUM_YIELD_TYPES; iI++)
				{
					iYield = 0;

					if (eImprovement != NO_IMPROVEMENT)
					{
						iYield += pMissionPlot->calculateImprovementYieldChange(eImprovement, ((YieldTypes)iI), pHeadSelectedUnit->getOwnerINLINE());
						if (pMissionPlot->getImprovementType() != NO_IMPROVEMENT)
						{
							iYield -= pMissionPlot->calculateImprovementYieldChange(pMissionPlot->getImprovementType(), ((YieldTypes)iI), pHeadSelectedUnit->getOwnerINLINE());
						}
					}

					if (NO_FEATURE != pMissionPlot->getFeatureType())
					{
						if (GC.getBuildInfo(eBuild).isFeatureRemove(pMissionPlot->getFeatureType()))
						{
							iYield -= GC.getFeatureInfo(pMissionPlot->getFeatureType()).getYieldChange(iI);
						}
					}

					if (iYield != 0)
					{
						szTempBuffer.Format(L", %s%d%c", ((iYield > 0) ? "+" : ""), iYield, GC.getYieldInfo((YieldTypes) iI).getChar());
						szBuffer.append(szTempBuffer);
					}
				}

				if (NO_IMPROVEMENT != eImprovement)
				{
					int iHappy = GC.getImprovementInfo(eImprovement).getHappiness();

					if (iHappy != 0)
					{
						szTempBuffer.Format(L", +%d%c", abs(iHappy), (iHappy > 0 ? gDLL->getSymbolID(HAPPY_CHAR) : gDLL->getSymbolID(UNHAPPY_CHAR)));
						szBuffer.append(szTempBuffer);
					}
				}

				bValid = false;

				pSelectedUnitNode = gDLL->getInterfaceIFace()->headSelectionListNode();

				while (pSelectedUnitNode != NULL)
				{
					pSelectedUnit = ::getUnit(pSelectedUnitNode->m_data);

					if (pSelectedUnit->canBuild(pMissionPlot, eBuild))
					{
						bValid = true;
						break;
					}

					pSelectedUnitNode = gDLL->getInterfaceIFace()->nextSelectionListNode(pSelectedUnitNode);
				}

				if (!bValid)
				{
					if (eImprovement != NO_IMPROVEMENT)
					{
						if (pMissionPlot->getTeam() != pHeadSelectedUnit->getTeam())
						{
							if (GC.getImprovementInfo(eImprovement).isOutsideBorders())
							{
								if (pMissionPlot->getTeam() != NO_TEAM)
								{
									szBuffer.append(NEWLINE);
									szBuffer.append(gDLL->getText("TXT_KEY_ACTION_NEEDS_OUT_RIVAL_CULTURE_BORDER"));
								}
							}
							else
							{
								szBuffer.append(NEWLINE);
								szBuffer.append(gDLL->getText("TXT_KEY_ACTION_NEEDS_CULTURE_BORDER"));
							}
						}

						if ((eBonus == NO_BONUS) || !(GC.getImprovementInfo(eImprovement).isImprovementBonusTrade(eBonus)))
						{
							if (!(GET_TEAM(pHeadSelectedUnit->getTeam()).isIrrigation()) && !(GET_TEAM(pHeadSelectedUnit->getTeam()).isIgnoreIrrigation()))
							{
								if (GC.getImprovementInfo(eImprovement).isRequiresIrrigation() && !(pMissionPlot->isIrrigationAvailable()))
								{
									for (iI = 0; iI < GC.getNumTechInfos(); iI++)
									{
										if (GC.getTechInfo((TechTypes)iI).isIrrigation())
										{
											szBuffer.append(NEWLINE);
											szBuffer.append(gDLL->getText("TXT_KEY_BUILDING_REQUIRES_STRING", GC.getTechInfo((TechTypes)iI).getTextKeyWide()));
											break;
										}
									}
								}
							}
						}
					}

					if (!(GET_TEAM(pHeadSelectedUnit->getTeam()).isHasTech((TechTypes)GC.getBuildInfo(eBuild).getTechPrereq())))
					{
						szBuffer.append(NEWLINE);
						szBuffer.append(gDLL->getText("TXT_KEY_BUILDING_REQUIRES_STRING", GC.getTechInfo((TechTypes) GC.getBuildInfo(eBuild).getTechPrereq()).getTextKeyWide()));
					}

					if (eRoute != NO_ROUTE)
					{
						if (GC.getRouteInfo(eRoute).getPrereqBonus() != NO_BONUS)
						{
							if (!(pMissionPlot->isAdjacentPlotGroupConnectedBonus(pHeadSelectedUnit->getOwnerINLINE(), ((BonusTypes)(GC.getRouteInfo(eRoute).getPrereqBonus())))))
							{
								szBuffer.append(NEWLINE);
								szBuffer.append(gDLL->getText("TXT_KEY_BUILDING_REQUIRES_STRING", GC.getBonusInfo((BonusTypes) GC.getRouteInfo(eRoute).getPrereqBonus()).getTextKeyWide()));
							}
						}

						bool bFoundValid = true;
						std::vector<BonusTypes> aeOrBonuses;
						for (int i = 0; i < GC.getNUM_ROUTE_PREREQ_OR_BONUSES(); ++i)
						{
							if (NO_BONUS != GC.getRouteInfo(eRoute).getPrereqOrBonus(i))
							{
								aeOrBonuses.push_back((BonusTypes)GC.getRouteInfo(eRoute).getPrereqOrBonus(i));
								bFoundValid = false;

								if (pMissionPlot->isAdjacentPlotGroupConnectedBonus(pHeadSelectedUnit->getOwnerINLINE(), ((BonusTypes)(GC.getRouteInfo(eRoute).getPrereqOrBonus(i)))))
								{
									bFoundValid = true;
									break;
								}
							}
						}

						if (!bFoundValid)
						{
							bool bFirst = true;
							for (std::vector<BonusTypes>::iterator it = aeOrBonuses.begin(); it != aeOrBonuses.end(); ++it)
							{
								szFirstBuffer = NEWLINE + gDLL->getText("TXT_KEY_BUILDING_REQUIRES_LIST");
								szTempBuffer.Format( SETCOLR L"<link=literal>%s</link>" ENDCOLR , TEXT_COLOR("COLOR_HIGHLIGHT_TEXT"), GC.getBonusInfo(*it).getDescription());
								setListHelp(szBuffer, szFirstBuffer.GetCString(), szTempBuffer, gDLL->getText("TXT_KEY_OR").c_str(), bFirst);
								bFirst = false;
							}
						}
					}

					if (pMissionPlot->getFeatureType() != NO_FEATURE)
					{
						if (!(GET_TEAM(pHeadSelectedUnit->getTeam()).isHasTech((TechTypes)GC.getBuildInfo(eBuild).getFeatureTech(pMissionPlot->getFeatureType()))))
						{
							szBuffer.append(NEWLINE);
							szBuffer.append(gDLL->getText("TXT_KEY_BUILDING_REQUIRES_STRING", GC.getTechInfo((TechTypes) GC.getBuildInfo(eBuild).getFeatureTech(pMissionPlot->getFeatureType())).getTextKeyWide()));
						}
					}
				}

				if (eImprovement != NO_IMPROVEMENT)
				{
					if (pMissionPlot->getImprovementType() != NO_IMPROVEMENT)
					{
						szBuffer.append(NEWLINE);
						szBuffer.append(gDLL->getText("TXT_KEY_ACTION_WILL_DESTROY_IMP", GC.getImprovementInfo(pMissionPlot->getImprovementType()).getTextKeyWide()));
					}
				}

				if (GC.getBuildInfo(eBuild).isKill())
				{
					szBuffer.append(NEWLINE);
					szBuffer.append(gDLL->getText("TXT_KEY_ACTION_CONSUME_UNIT"));
				}

				if (pMissionPlot->getFeatureType() != NO_FEATURE)
				{
					if (GC.getBuildInfo(eBuild).isFeatureRemove(pMissionPlot->getFeatureType()))
					{
						iProduction = pMissionPlot->getFeatureProduction(eBuild, pHeadSelectedUnit->getTeam(), &pCity);

						if (iProduction > 0)
						{
							szBuffer.append(NEWLINE);
							szBuffer.append(gDLL->getText("TXT_KEY_ACTION_CHANGE_PRODUCTION", iProduction, pCity->getNameKey()));
						}

						szBuffer.append(NEWLINE);
						szBuffer.append(gDLL->getText("TXT_KEY_ACTION_REMOVE_FEATURE", GC.getFeatureInfo(pMissionPlot->getFeatureType()).getTextKeyWide()));
					}

				}

				if (eImprovement != NO_IMPROVEMENT)
				{
					if (eBonus != NO_BONUS)
					{
						if (!GET_TEAM(pHeadSelectedUnit->getTeam()).isBonusObsolete(eBonus))
						{
							if (GC.getImprovementInfo(eImprovement).isImprovementBonusTrade(eBonus))
							{
								szBuffer.append(NEWLINE);
								szBuffer.append(gDLL->getText("TXT_KEY_ACTION_PROVIDES_BONUS", GC.getBonusInfo(eBonus).getTextKeyWide()));

								if (GC.getBonusInfo(eBonus).getHealth() != 0)
								{
									szTempBuffer.Format(L" (+%d%c)", abs(GC.getBonusInfo(eBonus).getHealth()), ((GC.getBonusInfo(eBonus).getHealth() > 0) ? gDLL->getSymbolID(HEALTHY_CHAR) : gDLL->getSymbolID(UNHEALTHY_CHAR)));
									szBuffer.append(szTempBuffer);
								}

								if (GC.getBonusInfo(eBonus).getHappiness() != 0)
								{
									szTempBuffer.Format(L" (+%d%c)", abs(GC.getBonusInfo(eBonus).getHappiness()), ((GC.getBonusInfo(eBonus).getHappiness() > 0) ? gDLL->getSymbolID(HAPPY_CHAR) : gDLL->getSymbolID(UNHAPPY_CHAR)));
									szBuffer.append(szTempBuffer);
								}
							}
						}
					}
					else
					{
						iLast = 0;

						FAssert((0 < GC.getNumBonusInfos()) && "GC.getNumBonusInfos() is not greater than zero but an array is being allocated in CvDLLWidgetData::parseActionHelp");
						for (iI = 0; iI < GC.getNumBonusInfos(); iI++)
						{
							if (GET_TEAM(pHeadSelectedUnit->getTeam()).isHasTech((TechTypes)(GC.getBonusInfo((BonusTypes) iI).getTechReveal())))
							{
								if (GC.getImprovementInfo(eImprovement).getImprovementBonusDiscoverRand(iI) > 0)
								{
									szFirstBuffer.Format(L"%s%s", NEWLINE, gDLL->getText("TXT_KEY_ACTION_CHANCE_DISCOVER").c_str());
									szTempBuffer.Format(L"%c", GC.getBonusInfo((BonusTypes) iI).getChar());
									setListHelp(szBuffer, szFirstBuffer, szTempBuffer, L", ", (GC.getImprovementInfo(eImprovement).getImprovementBonusDiscoverRand(iI) != iLast));
									iLast = GC.getImprovementInfo(eImprovement).getImprovementBonusDiscoverRand(iI);
								}
							}
						}
					}

					if (!(pMissionPlot->isIrrigationAvailable()))
					{
						GAMETEXT.setYieldChangeHelp(szBuffer, gDLL->getText("TXT_KEY_ACTION_IRRIGATED").c_str(), L": ", L"", GC.getImprovementInfo(eImprovement).getIrrigatedYieldChangeArray());
					}

					if (eRoute == NO_ROUTE)
					{
						for (iI = 0; iI < GC.getNumRouteInfos(); iI++)
						{
							if (pMissionPlot->getRouteType() != ((RouteTypes)iI))
							{
								GAMETEXT.setYieldChangeHelp(szBuffer, GC.getRouteInfo((RouteTypes)iI).getDescription(), L": ", L"", GC.getImprovementInfo(eImprovement).getRouteYieldChangesArray((RouteTypes)iI));
							}
						}
					}

					if (GC.getImprovementInfo(eImprovement).getDefenseModifier() != 0)
					{
						szBuffer.append(NEWLINE);
						szBuffer.append(gDLL->getText("TXT_KEY_ACTION_DEFENSE_MODIFIER", GC.getImprovementInfo(eImprovement).getDefenseModifier()));
					}

					if (GC.getImprovementInfo(eImprovement).getImprovementUpgrade() != NO_IMPROVEMENT)
					{
						iTurns = pMissionPlot->getUpgradeTimeLeft(eImprovement, pHeadSelectedUnit->getOwnerINLINE());

						szBuffer.append(NEWLINE);
						szBuffer.append(gDLL->getText("TXT_KEY_ACTION_BECOMES_IMP", GC.getImprovementInfo((ImprovementTypes) GC.getImprovementInfo(eImprovement).getImprovementUpgrade()).getTextKeyWide(), iTurns));
					}
				}

				if (eRoute != NO_ROUTE)
				{
					eFinalImprovement = eImprovement;

					if (eFinalImprovement == NO_IMPROVEMENT)
					{
						eFinalImprovement = pMissionPlot->getImprovementType();
					}

					if (eFinalImprovement != NO_IMPROVEMENT)
					{
						GAMETEXT.setYieldChangeHelp(szBuffer, GC.getImprovementInfo(eFinalImprovement).getDescription(), L": ", L"", GC.getImprovementInfo(eFinalImprovement).getRouteYieldChangesArray(eRoute));
					}

					iMovementCost = GC.getRouteInfo(eRoute).getMovementCost() + GET_TEAM(pHeadSelectedUnit->getTeam()).getRouteChange(eRoute);
					iFlatMovementCost = GC.getRouteInfo(eRoute).getFlatMovementCost();

					if (iMovementCost > 0)
					{
						iMoves = (GC.getMOVE_DENOMINATOR() / iMovementCost);

						if ((iMoves * iMovementCost) < GC.getMOVE_DENOMINATOR())
						{
							iMoves++;
						}
					}
					else
					{
						iMoves = GC.getMOVE_DENOMINATOR();
					}

					if (iFlatMovementCost > 0)
					{
						iFlatMoves = (GC.getMOVE_DENOMINATOR() / iFlatMovementCost);

						if ((iFlatMoves * iFlatMovementCost) < GC.getMOVE_DENOMINATOR())
						{
							iFlatMoves++;
						}
					}
					else
					{
						iFlatMoves = GC.getMOVE_DENOMINATOR();
					}

					if ((iMoves > 1) || (iFlatMoves > 1))
					{
						if (iMoves >= iFlatMoves)
						{
							szBuffer.append(NEWLINE);
							szBuffer.append(gDLL->getText("TXT_KEY_ACTION_MOVEMENT_COST", iMoves));
						}
						else
						{
							szBuffer.append(NEWLINE);
							szBuffer.append(gDLL->getText("TXT_KEY_ACTION_FLAT_MOVEMENT_COST", iFlatMoves));
						}
					}

					szBuffer.append(NEWLINE);
					szBuffer.append(gDLL->getText("TXT_KEY_ACTION_CONNECTS_RESOURCES"));
				}

				iNowWorkRate = 0;
				iThenWorkRate = 0;

				pSelectedUnitNode = gDLL->getInterfaceIFace()->headSelectionListNode();

				if (NULL != pHeadSelectedUnit)
				{
					if (GET_PLAYER(pHeadSelectedUnit->getOwnerINLINE()).getBuildCost(pMissionPlot, eBuild) > 0)
					{
						szBuffer.append(NEWLINE);
						szBuffer.append(gDLL->getText("TXT_KEY_BUILD_COST", GET_PLAYER(pHeadSelectedUnit->getOwnerINLINE()).getBuildCost(pMissionPlot, eBuild)));
					}
				}

				while (pSelectedUnitNode != NULL)
				{
					pSelectedUnit = ::getUnit(pSelectedUnitNode->m_data);

					if (pSelectedUnit->getBuildType() != eBuild)
					{
						iNowWorkRate += pSelectedUnit->workRate(false);
						iThenWorkRate += pSelectedUnit->workRate(true);
					}

					pSelectedUnitNode = gDLL->getInterfaceIFace()->nextSelectionListNode(pSelectedUnitNode);
				}

				iTurns = pMissionPlot->getBuildTurnsLeft(eBuild, iNowWorkRate, iThenWorkRate);


				szBuffer.append(NEWLINE);
				szBuffer.append(gDLL->getText("TXT_KEY_ACTION_NUM_TURNS", iTurns));

				if (!CvWString(GC.getBuildInfo(eBuild).getHelp()).empty())
				{
					szBuffer.append(CvWString::format(L"%s%s", NEWLINE, GC.getBuildInfo(eBuild).getHelp()).c_str());
				}
			}

			if (!CvWString(GC.getMissionInfo((MissionTypes)(GC.getActionInfo(widgetDataStruct.m_iData1).getMissionType())).getHelp()).empty())
			{
				szBuffer.append(CvWString::format(L"%s%s", NEWLINE, GC.getMissionInfo((MissionTypes)(GC.getActionInfo(widgetDataStruct.m_iData1).getMissionType())).getHelp()).c_str());
			}
		}

		if (GC.getActionInfo(widgetDataStruct.m_iData1).getCommandType() != NO_COMMAND)
		{
			if (GC.getActionInfo(widgetDataStruct.m_iData1).getCommandType() == COMMAND_PROMOTION)
			{
				GAMETEXT.parsePromotionHelp(szBuffer, ((PromotionTypes)(GC.getActionInfo(widgetDataStruct.m_iData1).getCommandData())));
			}
			else if (GC.getActionInfo(widgetDataStruct.m_iData1).getCommandType() == COMMAND_UPGRADE)
			{
				GAMETEXT.setBasicUnitHelp(szBuffer, ((UnitTypes)(GC.getActionInfo(widgetDataStruct.m_iData1).getCommandData())));

				if (bAlt && GC.getCommandInfo((CommandTypes)(GC.getActionInfo(widgetDataStruct.m_iData1).getCommandType())).getAll())
				{
					iPrice = GET_PLAYER(pHeadSelectedUnit->getOwnerINLINE()).upgradeAllPrice(((UnitTypes)(GC.getActionInfo(widgetDataStruct.m_iData1).getCommandData())), pHeadSelectedUnit->getUnitType());
				}
				else
				{
					iPrice = 0;

					pSelectedUnitNode = gDLL->getInterfaceIFace()->headSelectionListNode();

					while (pSelectedUnitNode != NULL)
					{
						pSelectedUnit = ::getUnit(pSelectedUnitNode->m_data);

						if (pSelectedUnit->canUpgrade(((UnitTypes)(GC.getActionInfo(widgetDataStruct.m_iData1).getCommandData())), true))
						{
							iPrice += pSelectedUnit->upgradePrice((UnitTypes)(GC.getActionInfo(widgetDataStruct.m_iData1).getCommandData()));
						}

						pSelectedUnitNode = gDLL->getInterfaceIFace()->nextSelectionListNode(pSelectedUnitNode);
					}
				}

				szTempBuffer.Format(L"%s%d %c", NEWLINE, iPrice, GC.getCommerceInfo(COMMERCE_GOLD).getChar());
				szBuffer.append(szTempBuffer);
			}
			else if (GC.getActionInfo(widgetDataStruct.m_iData1).getCommandType() == COMMAND_GIFT)
			{
				eGiftPlayer = pHeadSelectedUnit->plot()->getOwnerINLINE();

				if (eGiftPlayer != NO_PLAYER)
				{
					szBuffer.append(NEWLINE);
					szBuffer.append(gDLL->getText("TXT_KEY_ACTION_GOES_TO_CIV"));

					szTempBuffer.Format(SETCOLR L"%s" ENDCOLR, GET_PLAYER(eGiftPlayer).getPlayerTextColorR(), GET_PLAYER(eGiftPlayer).getPlayerTextColorG(), GET_PLAYER(eGiftPlayer).getPlayerTextColorB(), GET_PLAYER(eGiftPlayer).getPlayerTextColorA(), GET_PLAYER(eGiftPlayer).getCivilizationShortDescription());
					szBuffer.append(szTempBuffer);

					pSelectedUnitNode = gDLL->getInterfaceIFace()->headSelectionListNode();

					while (pSelectedUnitNode != NULL)
					{
						pSelectedUnit = ::getUnit(pSelectedUnitNode->m_data);

						if (!(GET_PLAYER(eGiftPlayer).AI_acceptUnit(pSelectedUnit)))
						{
							szBuffer.append(NEWLINE);
							szBuffer.append(gDLL->getText("TXT_KEY_REFUSE_GIFT", GET_PLAYER(eGiftPlayer).getNameKey()));
							break;
						}

						pSelectedUnitNode = gDLL->getInterfaceIFace()->nextSelectionListNode(pSelectedUnitNode);
					}
				}
			}

			if (GC.getCommandInfo((CommandTypes)(GC.getActionInfo(widgetDataStruct.m_iData1).getCommandType())).getAll())
			{
				szBuffer.append(gDLL->getText("TXT_KEY_ACTION_ALL_UNITS"));
			}

			if (!CvWString(GC.getCommandInfo((CommandTypes)(GC.getActionInfo(widgetDataStruct.m_iData1).getCommandType())).getHelp()).empty())
			{
				szBuffer.append(CvWString::format(L"%s%s", NEWLINE, GC.getCommandInfo((CommandTypes)(GC.getActionInfo(widgetDataStruct.m_iData1).getCommandType())).getHelp()).c_str());
			}
		}

		if (GC.getActionInfo(widgetDataStruct.m_iData1).getAutomateType() != NO_AUTOMATE)
		{
			if (!CvWString(GC.getAutomateInfo((ControlTypes)(GC.getActionInfo(widgetDataStruct.m_iData1).getAutomateType())).getHelp()).empty())
			{
				szBuffer.append(CvWString::format(L"%s%s", NEWLINE, GC.getAutomateInfo((ControlTypes)(GC.getActionInfo(widgetDataStruct.m_iData1).getAutomateType())).getHelp()).c_str());
			}
		}
	}

	if (GC.getActionInfo(widgetDataStruct.m_iData1).getControlType() != NO_CONTROL)
	{
		if (!CvWString(GC.getControlInfo((ControlTypes)(GC.getActionInfo(widgetDataStruct.m_iData1).getControlType())).getHelp()).empty())
		{
			szBuffer.append(CvWString::format(L"%s%s", NEWLINE, GC.getControlInfo((ControlTypes)(GC.getActionInfo(widgetDataStruct.m_iData1).getControlType())).getHelp()).c_str());
		}
	}

	if (GC.getActionInfo(widgetDataStruct.m_iData1).getInterfaceModeType() != NO_INTERFACEMODE)
	{
		if (!CvWString(GC.getInterfaceModeInfo((InterfaceModeTypes)(GC.getActionInfo(widgetDataStruct.m_iData1).getInterfaceModeType())).getHelp()).empty())
		{
			szBuffer.append(CvWString::format(L"%s%s", NEWLINE, GC.getInterfaceModeInfo((InterfaceModeTypes)(GC.getActionInfo(widgetDataStruct.m_iData1).getInterfaceModeType())).getHelp()).c_str());
		}
	}
}


void CvDLLWidgetData::parseCitizenHelp(CvWidgetDataStruct &widgetDataStruct, CvWStringBuffer &szBuffer)
{
	CvCity* pHeadSelectedCity;
	int iCount;
	int iI;

	pHeadSelectedCity = gDLL->getInterfaceIFace()->getHeadSelectedCity();

	if (pHeadSelectedCity != NULL)
	{
		if (widgetDataStruct.m_iData1 != NO_SPECIALIST)
		{
			GAMETEXT.parseSpecialistHelp(szBuffer, ((SpecialistTypes)(widgetDataStruct.m_iData1)), pHeadSelectedCity);

			if (widgetDataStruct.m_iData2 != -1)
			{
				iCount = 0;

				for (iI = 0; iI < GC.getNumSpecialistInfos(); iI++)
				{
					if (iI < widgetDataStruct.m_iData1)
					{
						iCount += pHeadSelectedCity->getSpecialistCount((SpecialistTypes)iI);
					}
					else if (iI == widgetDataStruct.m_iData1)
					{
						iCount += widgetDataStruct.m_iData2;
					}
				}

				if (iCount < pHeadSelectedCity->totalFreeSpecialists())
				{
					szBuffer.append(NEWLINE);
					szBuffer.append(gDLL->getText("TXT_KEY_MISC_FREE_SPECIALIST"));
				}
			}
		}
	}
}


void CvDLLWidgetData::parseFreeCitizenHelp(CvWidgetDataStruct &widgetDataStruct, CvWStringBuffer &szBuffer)
{
	CvCity* pHeadSelectedCity = gDLL->getInterfaceIFace()->getHeadSelectedCity();

	if (pHeadSelectedCity != NULL)
	{
		SpecialistTypes eSpecialist = (SpecialistTypes)widgetDataStruct.m_iData1;
		if (NO_SPECIALIST != eSpecialist)
		{
			GAMETEXT.parseSpecialistHelp(szBuffer, eSpecialist, pHeadSelectedCity);
		}
		if (widgetDataStruct.m_iData2 != -1)
		{
			szBuffer.append(SEPARATOR);
			GAMETEXT.parseFreeSpecialistHelp(szBuffer, *pHeadSelectedCity);
		}
	}
}


void CvDLLWidgetData::parseDisabledCitizenHelp(CvWidgetDataStruct &widgetDataStruct, CvWStringBuffer &szBuffer)
{
	CvCity* pHeadSelectedCity;
	CvWString szTempBuffer;
	BuildingTypes eLoopBuilding;
	bool bFirst;
	int iI;

	pHeadSelectedCity = gDLL->getInterfaceIFace()->getHeadSelectedCity();

	if (pHeadSelectedCity != NULL)
	{
		if (widgetDataStruct.m_iData1 != NO_SPECIALIST)
		{
			GAMETEXT.parseSpecialistHelp(szBuffer, ((SpecialistTypes)(widgetDataStruct.m_iData1)), pHeadSelectedCity);

			if (!(pHeadSelectedCity->isSpecialistValid(((SpecialistTypes)(widgetDataStruct.m_iData1)), 1)))
			{
				bFirst = true;

				for (iI = 0; iI < GC.getNumBuildingClassInfos(); iI++)
				{
					eLoopBuilding = (BuildingTypes)GC.getCivilizationInfo(GC.getGameINLINE().getActiveCivilizationType()).getCivilizationBuildings(iI);

					if (eLoopBuilding != NO_BUILDING)
					{
						if (GC.getBuildingInfo(eLoopBuilding).getSpecialistCount(widgetDataStruct.m_iData1) > 0)
						{
							if ((pHeadSelectedCity->getNumBuilding(eLoopBuilding) <= 0) && !isLimitedWonderClass((BuildingClassTypes)iI))
							{
								if ((GC.getBuildingInfo(eLoopBuilding).getSpecialBuildingType() == NO_SPECIALBUILDING) || pHeadSelectedCity->canConstruct(eLoopBuilding))
								{
									szTempBuffer = NEWLINE + gDLL->getText("TXT_KEY_REQUIRES");
									setListHelp(szBuffer, szTempBuffer, GC.getBuildingInfo(eLoopBuilding).getDescription(), gDLL->getText("TXT_KEY_OR").c_str(), bFirst);
									bFirst = false;
								}
							}
						}
					}
				}

				if (!bFirst)
				{
					szBuffer.append(ENDCOLR);
				}
			}
		}
	}
}


void CvDLLWidgetData::parseAngryCitizenHelp(CvWidgetDataStruct &widgetDataStruct, CvWStringBuffer &szBuffer)
{
	CvCity* pHeadSelectedCity;

	pHeadSelectedCity = gDLL->getInterfaceIFace()->getHeadSelectedCity();

	if (pHeadSelectedCity != NULL)
	{
		szBuffer.assign(gDLL->getText("TXT_KEY_MISC_ANGRY_CITIZEN"));
		szBuffer.append(NEWLINE);

		GAMETEXT.setAngerHelp(szBuffer, *pHeadSelectedCity);
	}
}


void CvDLLWidgetData::parseChangeSpecialistHelp(CvWidgetDataStruct &widgetDataStruct, CvWStringBuffer &szBuffer)
{
	CvCity* pHeadSelectedCity;

	pHeadSelectedCity = gDLL->getInterfaceIFace()->getHeadSelectedCity();

	if (pHeadSelectedCity != NULL)
	{
		if (widgetDataStruct.m_iData2 > 0)
		{
			GAMETEXT.parseSpecialistHelp(szBuffer, ((SpecialistTypes)(widgetDataStruct.m_iData1)), pHeadSelectedCity);

			if (widgetDataStruct.m_iData1 != GC.getDefineINT("DEFAULT_SPECIALIST"))
			{
				if (!(GET_PLAYER(pHeadSelectedCity->getOwnerINLINE()).isSpecialistValid((SpecialistTypes)(widgetDataStruct.m_iData1))))
				{
					if (pHeadSelectedCity->getMaxSpecialistCount((SpecialistTypes)(widgetDataStruct.m_iData1)) > 0)
					{
						szBuffer.append(NEWLINE);
						szBuffer.append(gDLL->getText("TXT_KEY_MISC_MAX_SPECIALISTS", pHeadSelectedCity->getMaxSpecialistCount((SpecialistTypes)(widgetDataStruct.m_iData1))));
					}
				}
			}
		}
		else
		{
			szBuffer.assign(gDLL->getText("TXT_KEY_MISC_REMOVE_SPECIALIST", GC.getSpecialistInfo((SpecialistTypes) widgetDataStruct.m_iData1).getTextKeyWide()));

			if (pHeadSelectedCity->getForceSpecialistCount((SpecialistTypes)(widgetDataStruct.m_iData1)) > 0)
			{
				szBuffer.append(NEWLINE);
				szBuffer.append(gDLL->getText("TXT_KEY_MISC_FORCED_SPECIALIST", pHeadSelectedCity->getForceSpecialistCount((SpecialistTypes)(widgetDataStruct.m_iData1))));
			}
		}
	}
}


void CvDLLWidgetData::parseResearchHelp(CvWidgetDataStruct &widgetDataStruct, CvWStringBuffer &szBuffer)
{
	TechTypes eTech;

	eTech = ((TechTypes)(widgetDataStruct.m_iData1));

	if (eTech == NO_TECH)
	{
		//	No Technology
		if (GET_PLAYER(GC.getGameINLINE().getActivePlayer()).getCurrentResearch() != NO_TECH)
		{
			CvGameAI& game = GC.getGameINLINE();
			CvPlayer& activePlayer = GET_PLAYER(game.getActivePlayer());
			szBuffer.assign(gDLL->getText("TXT_KEY_MISC_CHANGE_RESEARCH"));
			szBuffer.append(NEWLINE);
			GAMETEXT.setTechHelp(szBuffer, activePlayer.getCurrentResearch(), false, true);
		}
	}
	else
	{
		GAMETEXT.setTechHelp(szBuffer, eTech, false, true, widgetDataStruct.m_bOption);
	}
}


void CvDLLWidgetData::parseTechTreeHelp(CvWidgetDataStruct &widgetDataStruct, CvWStringBuffer &szBuffer)
{
	GAMETEXT.setTechHelp(szBuffer, ((TechTypes)(widgetDataStruct.m_iData1)), false, false, false, false);
}


void CvDLLWidgetData::parseChangePercentHelp(CvWidgetDataStruct &widgetDataStruct, CvWStringBuffer &szBuffer)
{
	if (widgetDataStruct.m_iData2 > 0)
	{
		szBuffer.assign(gDLL->getText("TXT_KEY_MISC_INCREASE_RATE", GC.getCommerceInfo((CommerceTypes) widgetDataStruct.m_iData1).getTextKeyWide(), widgetDataStruct.m_iData2));
	}
	else
	{
		szBuffer.assign(gDLL->getText("TXT_KEY_MISC_DECREASE_RATE", GC.getCommerceInfo((CommerceTypes) widgetDataStruct.m_iData1).getTextKeyWide(), -(widgetDataStruct.m_iData2)));
	}
}


void CvDLLWidgetData::parseContactCivHelp(CvWidgetDataStruct &widgetDataStruct, CvWStringBuffer &szBuffer)
{
	//	Do not execute this if we are trying to contact ourselves...
	if (widgetDataStruct.m_iData1 >= MAX_PLAYERS || GET_PLAYER((PlayerTypes)widgetDataStruct.m_iData1).getCivilizationType() == NO_CIVILIZATION)
	{
		return;
	}
	if (GC.getGameINLINE().getActivePlayer() == widgetDataStruct.m_iData1)
	{
		parseScoreHelp(widgetDataStruct, szBuffer);
		return;
	}

	szBuffer.assign(gDLL->getText("TXT_KEY_MISC_CONTACT_LEADER", GET_PLAYER((PlayerTypes)widgetDataStruct.m_iData1).getNameKey(), GET_PLAYER((PlayerTypes)widgetDataStruct.m_iData1).getCivilizationShortDescription()));

	szBuffer.append(NEWLINE);
	GAMETEXT.parsePlayerTraits(szBuffer, (PlayerTypes)widgetDataStruct.m_iData1);

	if (!(GET_TEAM(GC.getGameINLINE().getActiveTeam()).isHasMet(GET_PLAYER((PlayerTypes)widgetDataStruct.m_iData1).getTeam())))
	{
		szBuffer.append(NEWLINE);
		szBuffer.append(gDLL->getText("TXT_KEY_MISC_HAVENT_MET_CIV"));
	}
	else
	{
		if (!(GET_PLAYER((PlayerTypes)widgetDataStruct.m_iData1).isHuman()))
		{
			if (!(GET_PLAYER((PlayerTypes)widgetDataStruct.m_iData1).AI_isWillingToTalk(GC.getGameINLINE().getActivePlayer())))
			{
				szBuffer.append(NEWLINE);
				szBuffer.append(gDLL->getText("TXT_KEY_MISC_REFUSES_TO_TALK"));
			}

			szBuffer.append(NEWLINE);
			GAMETEXT.getAttitudeString(szBuffer, ((PlayerTypes)widgetDataStruct.m_iData1), GC.getGameINLINE().getActivePlayer());

			szBuffer.append(NEWLINE);
			GAMETEXT.getEspionageString(szBuffer, ((PlayerTypes)widgetDataStruct.m_iData1), GC.getGameINLINE().getActivePlayer());

			szBuffer.append(gDLL->getText("TXT_KEY_MISC_CTRL_TRADE"));
		}
		else
		{
			szBuffer.append(NEWLINE);
			GAMETEXT.getEspionageString(szBuffer, ((PlayerTypes)widgetDataStruct.m_iData1), GC.getGameINLINE().getActivePlayer());
		}

		if ((GET_PLAYER((PlayerTypes)widgetDataStruct.m_iData1).getTeam() != GC.getGameINLINE().getActiveTeam()) && !(GET_TEAM(GC.getGameINLINE().getActiveTeam()).isAtWar(GET_PLAYER((PlayerTypes)widgetDataStruct.m_iData1).getTeam())))
		{
			if (GET_TEAM(GC.getGameINLINE().getActiveTeam()).canDeclareWar(GET_PLAYER((PlayerTypes)widgetDataStruct.m_iData1).getTeam()))
			{
				szBuffer.append(NEWLINE);
				szBuffer.append(gDLL->getText("TXT_KEY_MISC_ALT_DECLARE_WAR"));
			}
			else
			{
				szBuffer.append(NEWLINE);
				szBuffer.append(gDLL->getText("TXT_KEY_MISC_CANNOT_DECLARE_WAR"));
			}
		}
	}

	if (GET_PLAYER((PlayerTypes)widgetDataStruct.m_iData1).isHuman())
	{
//		szBuffer += "\n(<SHIFT> to Send Chat Message)";
		szBuffer.append(NEWLINE);
		szBuffer.append(gDLL->getText("TXT_KEY_MISC_SHIFT_SEND_CHAT"));
	}
}


void CvDLLWidgetData::parseConvertHelp(CvWidgetDataStruct &widgetDataStruct, CvWStringBuffer &szBuffer)
{
	if (widgetDataStruct.m_iData2 != 0)
	{
		if (widgetDataStruct.m_iData1 == NO_RELIGION)
		{
//			szBuffer.Format(L"No State %c", gDLL->getSymbolID(RELIGION_CHAR));
			szBuffer.assign(gDLL->getText("TXT_KEY_MISC_NO_STATE_REL"));
		}
		else
		{
//			szBuffer.Format(L"Convert to %s", GC.getReligionInfo((ReligionTypes) widgetDataStruct.m_iData1).getDescription());
			szBuffer.append(gDLL->getText("TXT_KEY_MISC_CONVERT_TO_REL", GC.getReligionInfo((ReligionTypes) widgetDataStruct.m_iData1).getTextKeyWide()));
		}
	}
	else
	{
		GAMETEXT.setConvertHelp(szBuffer, GC.getGameINLINE().getActivePlayer(), (ReligionTypes)widgetDataStruct.m_iData1);
	}
}


void CvDLLWidgetData::parseRevolutionHelp(CvWidgetDataStruct &widgetDataStruct, CvWStringBuffer &szBuffer)
{
	if (widgetDataStruct.m_iData1 != 0)
	{
//		szBuffer = "Change Civics";
		szBuffer.assign(gDLL->getText("TXT_KEY_MISC_CHANGE_CIVICS"));
	}
	else
	{
		GAMETEXT.setRevolutionHelp(szBuffer, GC.getGameINLINE().getActivePlayer());
	}
}

/*void CvDLLWidgetData::parsePopupQueue(CvWidgetDataStruct &widgetDataStruct, CvWString &szBuffer)
{
	PopupEventTypes eEvent;

	if ( m_pPopup || m_pScreen )
	{
		if ( m_pPopup )
		{
			eEvent = m_pPopup->getPopupType();
		}
		else if ( m_pScreen )
		{
			eEvent = m_pScreen->getPopupType();
		}

		switch (eEvent)
		{
			case POPUPEVENT_NONE:
//				szBuffer = "***NO MOUSEOVER TEXT***.  Click to activate popup.";
				szBuffer = gDLL->getText("TXT_KEY_MISC_NO_MOUSEOVER_TEXT");
				break;

			case POPUPEVENT_PRODUCTION:
//				szBuffer = "Production Complete";
				szBuffer = gDLL->getText("TXT_KEY_MISC_PRODUCTION_COMPLETE");
				break;

			case POPUPEVENT_TECHNOLOGY:
//				szBuffer = "Technology Research Complete";
				szBuffer = gDLL->getText("TXT_KEY_MISC_TECH_RESEARCH_COMPLETE");
				break;

			case POPUPEVENT_RELIGION:
//				szBuffer = "New Religion Discovered";
				szBuffer = gDLL->getText("TXT_KEY_MISC_NEW_REL_DISCOVERED");
				break;

			case POPUPEVENT_WARNING:
//				szBuffer = "Warning!!!";
				szBuffer = gDLL->getText("TXT_KEY_MISC_WARNING");
				break;

			case POPUPEVENT_CIVIC:
//				szBuffer = "New Civic Accessible";
L.h"
#include gDLL->getText("TXT_KEY_MISC_NEWvGameC_ACCESSIBLE")includebreakinclu}
h"
}*/

void CvDLLWidgetData::parseAutomateCitizensHelp(Cvinclude "CStruct &w
#include "CvP, CvWString#includ&
#inclu)
{
	CvCity* pHeadSelectedArgs;e "C	st.h"
#include ".h"
#includInterfaceIFace()ncludt.h"
#include "(nclu
	if (TextMgr.h"
#inclu!= NULL)
	de "aceBase.h"
#include "->isude "CvT"
#incld()ineIIFacDLL.h
#include "Turn Off ude "Cv "
#incion#includ
#inclu.assign(
#include "CvUnit.h"
#inclOFF_CITIZEN_AUTO")nclude"
#	elsee "CvDLLWidgetData.h"
#includn"CvPopupInfo.h"
#include "FProfiler.h"
#include "CvMessageControl.h"N
CvDLLWidgetData* CvDLLWiincle "CvMap.h"
#include "CvPlot.h"
#inclProduc
#ieamAI.h"
#include "CvPlayerAI.h"
#include "CvGameCoreUtils.h"
#include "CyArgsList.h"
#include "CvGameTextMgr.h"
#include "CvDLLInterfaceIFaceBase.h"
#include "CvDLLPythonIFaceBase.h"
#include "CvDLLEngineIFaceBase.h"
#include "CvEventvDLLWidget.h"
#include "CvDLLWidgetData.h"
#include "vDLLWidgetInfo.h"
#include "FProfiler.h"
#include "CvMessageControl.h"

PRODdgetData* CvDLLWidgetData::m_pInst = NULL;

CvDLLWid
	case WIDGET_PLOT_LIST_SHIFT:
		szBuffer.assign(gDLL->getText("TXT_KEYNISC_CTRL_SHIFT", (GC.getData;
	}
	return *m_pInst;
}
EmphasizeeamAI.h"
#include "CvPlayerAI.h"
#include "CvGameCoreUtils.h"
#include "CyArgsList.h"
#include "CvGame"FProfileclearythonIFaTextMgr.h"
#include "CvDLLInterfaceIFaceBase.h"
#include "CvDLLPythonIFaceBase.h"
#include "CvDLLEngineIFaceBase.h"
#include "CvEveAI_isuffer);
((uffer);
Types)yerAI.h"
#inclu.m_ie "C1ude "CvDLLWidgetData.h"+
#include "nclude "FProfilerppend#include "CvMessageControl.h"TURN"
ata* CvDLLWidgetData::m_pInst = NULL;end(gDLL->ntText("TXT_KEY_WIDGET_DELETE_GROUP"));
		break;

	case N
		parseLiberae WIDGET_UNIDGET_DEGC.getuffer);
InfoGROUP"));
		break;

	case WIDGET_DELETE_);
Descrip
#i(ta* CdgetD"CvMap.h"
#include "CvPlot.hTradeItemI.h"
#include "CvPlayerAI.h"
#include "CvGameCoreUtils.h"
#include "CyCvGameC szTemp#incluinclTAIN:e "C iteminclPlayer		bre eWhoFrom = NO_PLAYERuct, szBuffer);
		bTo;

	case WIDGEDenialfer);
LL->geuct, szBuffer);
		bLL->escase WIDGET_UNIT_NAME:
		szceBak;

	case WIDGET_bOct, sineIFaceBase."
#incisDiplomacylude "CvDL			
		break;
( szBuffer);)"
#includ
	case WI szBufythonvDLLWidgetD ceBareak;
MP
	case WIScreenUpDGET_ACTION:
		parseActionHelp(widgetDataStrucZEN:
		parer);
		break;

	
		szBufer);
GameINLINE(getDaActiveer);
		brea"
#getDataTION:
		break;
eeCitizenHelp(widgetDataStruct, szBuffer;
		break;

	case WIDG ET_ACTION:
		pszBufionHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_CITIZEN:
		parseCitizenHelp(widgetDataSreak;

	case WIDGET_ANGRY_
	case WIDGET_FREE_CITIZEN:dgetDa

	case W =
		breakhonIFaceBa(
		break;vDLL
	case W) && k;
Tose WIDGET_RESEineIFaceB//	ELETE is the headingitizswitchriptHelp(widgetDataStDELETE_T_ACTION:case TRADE_TECHNOLOGIES:ION:GAMETEXT.sude cheamAI
#inclu, ((	bre		break;

	case WIDGET_DELET2ta* CvDetDataStruct, iptHelp(widgetDataStruct, s ?
		break;::
		sznclude CvGameAI.hhTreeHelp(wRESOURCtruct, szBuffer);
	BonuTeamAI
	case WIDGormatHANGE_PERCENT:
		parseChangePercentHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_CITY_TAB:
		{
			CvWString szCvDLtruct, s"FProfiler.h"
#include "CvMessageContrET_CONTACT_Cata* CvDlp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_CITY_TAB:
		{
			CvWString szPEACEIV:
		parseContGET_DELETE_GROUP"));
		breakHelp(wMAKak;

", GET_TEAM(Y_ZOcase Wk;

	cagetDaTeam()getDaName().GetCvGameC()KEY_ZOOM_CI(
	caHANGE_PERCENT:
		parseChangePerWIDGET_END_TURN:
		szB	break;
		{
			CvWString szWAR	case WIDGET_ZOOM_CITY:
		szBuffer.append(gDLL->getTextWAR_KEY_ZOOM_CITY_HELP"));
		break;

	case WIDGET_END_TURN:
		szBuffer.append(gDLL->getText("TXT_KEY_WIDGET_END_TURN"));
		break;
		
	case WIDGET_LAUNCH_VICTORY:EMBARGO	case WIDGET_ZOOM_CITY:
		szBuffer.append(gDLL->geSTOPDLL->ING_KEY_ZOOM_CITY_HELP"));
		break;

	case WIDGET_END_TURN:
		szBuffer.append(gDLL->getText("TXT_KEY_WIDGET_END_TURN"));
		break;
		
	case WIDGET_LAUNCH_VICTORY:GameCorese WIDGET_ZOOM_CITY:
		szBuffer.append(gDLL->geADOPCvGameC_KEYr);
meCor

	cameCorL->getText("TXT_KEY_WIDGET_END_TURN"taStruct, szBuY_TAB:
		{
			CvWString szTeLIGION WIDGET_UNIT_MODEL:
		parseUnitModelHelp(widgetDatCONVERTase WIDGEBuffer);Religion

	cabreak;
se WIDGET_FLAG:
		parseFlagHelp(widgetDataStruct, szBuffer);
		break;

	caGOLD WIDGET_UNIT_MODEL:
		parseUnitModelHelp(widgetDat
	ca		break;Buffer);
		break;

	ca_PER
	casse WIDGET_HELP_RELIGION_CITY:
		parseReligionHelpCity(eak;

	widgetDataStruct, szBuffer);
MAPCIV:
		parseContM_CITY:
		szBuffer.append(gDLL->getTP
		break;
		{
			CvWString szSURRENDE	szBuffer.append(gDLL->getText("TXT_KEY_WIDGET_LAUNCCAPITULATEtyHelp(widgetDataStruct, szBufVASSAL WIDGET_UNIT_MODEL:
		parseUnitModelHelp(widgetDatelp(wityHelp(widgetDataStruct, szBufOPEN_BORDEReak;

	case WIDGET_HELP_NATIONALITY:
		parseNatioelp(widgetDatyHelp(widgetDataStruct, szBufDEFENSIVE_PACT WIDGET_UNIT_MODEL:
		parseUnitModelHelp(widgetDatDataStruct, sztyHelp(widgetDataStruct, szBufPERMAN "CvALLIAN
	case WIDGET_ZOOM_CITY:
		szBuffer.append(gDLL->geBuffer);
		break;ctionHelp(widgetDataStruct, szBuACE_TREATY

	case WIDGET_HELP_CULTURE:
		parseCultureHelp(wiDGET_HELP_Buffer);DefineINT("uct, szBuffe_LENGTH"t, szBuffer);
		brdgetDa	
		AIN:
		p&aStrWIDGEAIN:abl:
		s)
	case WIDGET_TECH_TREE:
	), PERCENT:
		parseChangePerhonIFa	"TXT_KEDGETY_HELP"));
		break;

widgeL->ge:
		pa,taStrtedHelp(ceBawidgetDae WIDGDENIAgineICTION:		parseHurry.Format(L"%s: " SETCOLR 		br" END
	caKEY_ZOELP"));
		case WTURN"));
	, fer)_COLOR("Help(CTORNING_fer)"Buff
		brea->ge

	c

	cagetDataStruct, szBuffe

	case WIDGET_HENEWp(winclude 
	case WIDGET_HE		parseHurry		parseLiberateCit"CvMap.h"
#include "CvPlot.hUnitModeleamAI.h"
#include "CvPlayerAI.h"
#include "CvGameCoreUtils.h"
#include "CyarseList.h"
#incluarseCvGameTextMgr.h"
#arseude "CvDLLInterfaceIFaceBase.h"
#include "CvarseythonIFaceBase.h"
#incluuct, vDLLEngineIFaceBzBuffer);
	arse(L"%s", GC.getCObsoleteHelp(widguffer);	case WIDGET_HELP_TECH_ENTRY:
		pFlageamAI.h"
#include "CvPlayerAI.h"
#include "CvGameCoreUtils.h"
#include "CyHURRY:
		parseHurryHele WIDruct, szBuffer);


	case WIDGET_HELP_TeCityHelp(widgetDaHIGHLIGHZOOMszBuffer);
meColiz"
#i

	ceeCitizenHelp(widgetDataStruetDataStruct		brse WIDGT_HELP_ESPIONAGE_CidgetDataStruct, szBuffer);
		brT:
		parseEspionageCostHel
Buffer);
lot.hLeaderTraitss", GC.getCStruct, szBeeCitizenHelp(widgetDataStruct, szBuTURN"ION:
	EE_UNroductionHelp(widgetDataStruct, szBuffer);
		break;
IDGET_HELP_FREE_UNIffer);
		break;

	case WIDGET_MAINMaintenanc
		break;

	case WIDGET_CITY_NAME:
		parseCityNameHelp(widgetDataStruct, szBuffer);
		break;

	cas	wchar
		parseHurry[1024]eHeaint iROUTES:
		ValueCvGameTextMgr.h"
#include "CvDLLInterfaceIFaceBase.h"
#include "CvDLLPythonIFaceBase.h"
#include "CvDLLEngineIFaceBase.h"
#include "CvEventWeLoveTheKingDaIDGET_ACTION:T:
		parseEspionageCostHelp(widgetDataStruct,
#include "CvUnit.h"
#inclWE_LOVE_KructMAINuctionHelLLWidgetData::m_	tDatagetData.h"
#ROUTES:
		 represent szBuftotal cost of governY:
this city.\include "FProfiler.h"
#include "CvMessageControl.h"t, sz_INFData* CvD		break;

	case WIDGET_HELP_F		Buffer);
		break =ist.h"
#include "->calculateDist
		ROUTES:
		Times100		breakING:
	case WIDGET_HEL!= 0		par
	casee WID	swprintf, szBuffer);, "\n%s%d%c: %s"WIDG
	case WIDGET_HEL> 0) ?  "+" : "BuffBuffer);
		breakuffer);
ommerc

	cCOMMERCpCity(tDataShAME:WIDGStruct, szBMAP_TRADE:
		parsegetOwnerelp(widgTURN")umGtructmentCeerfas()

	case"elp(widg feak;PalaceDGET_No
		bre Penalty(widgetDaeObsoleteSpecROUTE =e "CvGameC::fer);
		bd.%02d"LP_GOLD_TRADE:
		p/100LP_GOLD_TRADE:
		p%100nclude "T:
		parseEspionageCostHelp(wase WIDGET_HELP_LOS_BONUS:
		parseLOSHelp(wiNUMpRevealFLOAT",
		parse	break;
		
	 +
		break;

	case WIDGET_HELP_OPEN_BORDERS:
		parseOpenBordersHelp(widgetDataStru
#include "CvUnit.h"
#inclDISTeak;_FROM_PALTXT_) :"
#include "CvUnit.h"
#incluOdgetDat_PENALTYT_GENERAL:reatGen

	case WIDGET_HELP_MAP_TRADE:
		parseMapTradeHNumude esetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_TECH_TRADE:
		parseTechTradeHelp(widgetDataStrucNumberDatareak; szBuffer);
		break;

	caseWIDGET_HELP_GOLD_TRADE:
		parseGoldTradeHelp(widgetDataStruct, szBuffer)_DEFENSIVE_PACT:
		parseDefensivePactHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_PERMANENT_ALLIANCE:
		parsePermanentAllianceHelp(widgetDataStruct, szBuffer);
		breaTACT_C
	case WIDGET_HELP_VASSAL_STATRIGATION:
		parseIrrigationHelp(widgetDataStruct, szBuffer);
ColonyetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_TECH_TRADEVE_PACT:
		parseDefensivePactHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_PERMANENT_ALLIANCE:
		parsePermanentAllianceHelp(widgetDataStruct, szBuffer);
		HelpNYak;

	case WIDGET_HELP_VASSAL_STAT(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_TERRrpor"
#iTRADE:
		parseTerrainTradeHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_SPECIAL_BUILDING:
		parseSpecialBuildingHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_YIELD_CHANGE:
		parseYieldChangeHelp(widgetDatRPORATIONuct, szBuffer);
		break;

	case WIDGET_HELP_BONU
	case WIDGET_HESEPARATOR	break;
 WIDGarseTechTradeHelp(widgetDad%c Tlp(wiROUTES:
		"DGET_HELP_OBSOLHELP_OPENROUTES:
		DGET_zBuffer);
		break;

	case WIDGET_HELP_IMPROVEMVE_PACT:
		parseDefensivePactHelp(widgetDataStrucuct, szBuffer);
		break;

	cast, szBuffebreak; WIDGET_HELP_FINANCE_UNIT_COST:
		parseFinHELP_PERMANt, szBuffer);
		break;

	case WIDGET_HELP_LOS_BONUS:
		parseLOSHelp(wiTOTALuct, szBuffer);
		break;

	case WIDGEak;

	case WIDGET_HELP_MAP_TRADE:
		parsebreak;

	casModifi
		bre);
		break;

	case WIDGET_HELP_TECH_TRADEORATION:
		parseFoundCL" (ataSt%) szBuffer);
		break;

	caseLWIDGETL_HELP_GOLD_TRADE:
		prmanentAllianceHelp(widg szBuffer);
		bre;
		bak;

	case WIDGET_HELP_TECH_ENTRY:
		pHealteak;
.h"
#include "CvPlayerAI.h"
#include "CvGameCoreUtils.h"
#include "CyArgsList.h"
#include "ude "CvDLLInterfaceIFaceBase.h"
#include "CvDLLPythonING:LEngET_Hst.h"
#include "ruct, szBuffer);
		bBad		break;

	case WI*FinanceGrossIncomeGE_CO
	case WIDGET_HEL"\n=inanceNetGold(widgetDa\nincludezBuffer);
	Goouffer);
		break;

	case WIDGET_HELP_FINANC:
		parseObsoleteBonusString(widgetDN"
#ialityeamAI.h"
#include "CvPlayerAI.h"
#include "CvGameCoreUtils.h"
#include "lthRateHelp(widgetDataStructHELP_HEALTH_RATE:
		parseHea szBuffer);
Cultural_BORDruct, szB_TO_REePeHelneqHeH:
		pityStrengthrereq(widGarrisonrereq(widIcase WIDGET_UNIr.h"
#include "CvMessageControl.h"CITY_N	parsALILP_IRCvGameTextMgr.h"
#include "CvDLLInterfaceIFaceBase.h"
#include "CvDLLPythonIFaceBase.h"
#include "CvDLLEngineIFaceBfor (iI = 0; iI < MAXE_ROUTES
		b++ET_ACTION:ceBaStruct, szBionHelp(widgeiI).isAliv_UNIP_TECH_TRADE	parseTechTreePLP_MAP_TRADE:
		parseplotse.hT_HELP_TERarseTechTreeP
		parseBuildingffer);
		breazBuffer);
		br
	cncludeH_TRADECIVIC_UPKEEP:
		parseFinarpora%ak;

	case WIDGET_HELP_T
		break;

	roductionHelp
		parseBuildingHget szBuffextRRAIrRDGET_HELP_WORKET_PEDIA_JUMP_TO_BONUS:
		parseBonuGHelp(widgetDataStruct, szBuffer);
		break;

	caBHelp(widgetDataStruct, szBuffer);
		break;

	caAHelp(widgetDataStruct, szBuffer);
etDataStructAdjeaStru_IMPROVEMEINANCE_FOREIGN_INCOME:
		parseFinan;
		bnceForeigelp(w_TO_REQUIRED_reak;

	case WIDGET_PEDIA_BACK:
		// parseQUIRED_ythonIFaING:
uct, szBuffer)e WIDGET_RESE_PEDIA_JUMP_TO_BUILDING:nitCombatHelp(k;

	casearseFinanceGrossIncomnclude case DataStruct, szetDataStrucLP_MAP_TRADE:
		parseMarseTeataStruc

	case WIDGETincludefer, fals, szBuffer);
		break;

	caer, falsT_PEDIA_JUMP_TO_CIVszBuffer);
tDataStruct,>ffer, fals WIDGET_PEDIA_FORWARD:
		// parsePediaF%.2f WIDtd::max(0.0f, (1.0f - (((float)
		parseC / _PEDIA_JUIA_JUMP_TO_C)))) *R:
		par(		breain(10

	casPEDIA_J_IMPROVEMENT:
		parseRevoltTestProbabiuct,e WI WIDGET_HNENT_ALLIANCE:
		parsePermanentAYIELD_CHANGE:
		parseYieldChangeHelp(widgetDaHgeHelOF_REVOLe WIDGzBuffer);
arseEventHelp(widgetDanIncome(widgetDataStruct, szBuffer);
	appinesTeamAI.h"
#include "CvPlayerAI.h"
#include "CvGameCoreUtils.h"
#include "CyArgsList.h"
#include "CvGameTextMgr.h"
#include "CvDLLInterfaceIFaceBase.h"
#include "CvDLLPythonIFaceBase.h"
#include "CvDLLEngineIFaceBzBuffer);
	Anger
		break;

	case WIDGET_HELP_FINANCE_NET_GOLD:
		parseFinanceNetGold(widgetDataStruct, szBuffer);
truc, szBuse WIDGET_HELP_FINANCE_GOLD_RESERVE:
		parseFinanceGoldReserve(widgetPopradegetData::freeInstance()
{
	delete m_pInst;
	m_pInst = NULL;
}

void CvDLLWidgetData::parseHelp(CvWStringBuffer &szBuffer, CvWidgetDataStruct &widgetDataStruct)
{
	switch (widgetDataStruct.m_eWidgetType)
	{
	case"FProfiler.h"
#include "CvMessageControl.h"FOOD_THRESHty(wUnitCost(widgetDataStrucFoodr);_IMPROVEMENT:
		parrowthThresholclud
	case WIDGET_PEDIA_JUMP_TO_TERRAIN:
		parDLLWidgetData::freeInstance()
{
	delete m_pInst;
	m_pInst = NULL;
}

void CvDLLWidgetData::parseHelp(CvWStringBuffer &szBuffer, CvWidgetDataStruct &widgetDataStruct)
{
	switch (widgetDataStruct.m_eWidgetType)
	{
	case WIDGET_PLOT_LIST:
		pONUSDLLWidgetNeedncluwidgk;
INTuct, szBuffObsoleteSpecialHGE_COST:parsffer);
		brea%d/%d %c
		//parseCloseScreenHelaStruct, szadeRoutruct, szBuffer);
		break;

	cWIDGET_LEADER_LINE:
		parseLeaderLizBuffer)WIDGET_HYield

	cYIEnHelRODUCparsDGET_HELP_IMPROVEM"FProfiler.h"
#arseLe
		break;

	case WIDGET_HELP_TECH_ENTRY:
		p parsePeamAI.h"
#include "CvPlayerAI.h"
#include "CvGameCoreUtils.h"
#include "CyArgsList.h"
#include "CvGameTextMgr.h"
#include "CvDLLInterfaceIFaceBase.h"
#include "CvDLLPythonIFaceBase.h"
#include "CvDLLEngineIFaceBa
		parseTet, szBuf		parseFinanceCityMaint(w= false;

	sw
	case WIDGET_HELP_OPEN_BORDERS:
		pCitizenHe = false;

	swHELP =_HELP_TEaStruct, szBuffeGET_PEDIA_JUMP_TO_DERIVED_TECH:
		ULTURT_KE = false;

	swanceUnitCost(widgetDataStruc= false;DGET_DEAL_KILL:;
		break;

	caseObsoleteSpec parsePDefensivePactHelp(widgetDataStructangePlotListColumn(wigetDataStruct);
		bCommerceModHelp(widgetDSHIFT:
		gDLL->getInterfaceIFace()
	case WIDG parseP_TURN:
		szBufdgetDataStruct.m_iData1 * ((gDLL->ctrlKey()) ? (GCith this = falseRate;

	switch (widgetDataStruct.m_eradeHel;

	case WdgetDataStIFace()otList(widgetDataS;

	case WIase WIDGIA_JUMP
		parseTeLeft;

	switc		brList.h"
#include "iData1 * ((gDLL->ctrlKe -	if ( widgetDataSffer);
		brecase WIDGET_UNIT_NAMase WIDGEtruct, s szBinclsDGETtaSt);
		break;

	case +
		break;

	case WI- 1ADER_NAME:
		doRenameCiase WIDGE_NET_GOLD:
		par' 'rmanentAllianceHelp(widgetDataStruct, sINTERFWIDG	pars	casS;
		break;1,P:
		doDel WIDGET_HELPION:
	ANCE_NET_GOLD:
		parseFinanceNetGold(widgetDataStruct, szBuffer);
oLiberattaStruct, szBuffer);
		break;
, reak;

	case WIDGET:
		parseObsoleteBonusString(widgetDGreatPeoplnctions...
bool CvDLLWidgetData::executeAction( CvWidgetDataStruct &widgetDataStruct )
{
	bool bHafer);
		break;

	case WIDGET_HELP_FINANCE_GROSS_INCOME:
		parseFinanceGrossIncome(widgetDataStructU_ICON:
		doMenu();se WIDGET_HELP_FINANCE_GOLD_RESERVE:
		parseFinanceGoldReserve(widgetN:
	GeneraEntryHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_TECH_PME:

	case WwidgeeCitizenHt, szBuffer);
		breaZEN:
		break;

	case WIDET_CHANGE_SPFeatureProductionHelp(widgetDatt, szBuffer);
		breatruct);
		break;

	case WIDGET_MENU_ICO
#incluparseTradeRouteHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_HEALTH_RATE:
		parseHeaREPREQ:
		parseTechPrereqHe	Ordere "C* p_END_CvGameTextMgr.h"
#include "CvDLLInterfaceIFaceBase.h"
#include "CvDLLPython(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_OBSOLETE:
		parseObsoleteHelp(de "CvDLLEngineIFaceB
		GC.		parseFinanceCityMaint(w_END_reakQueue
	case WIDGET_TECH_TREE:
	:
		parseU		breakvDLLEngineI	case WIak;


		GC.->e_END_e WIementHelp(wihTreedgetDDLL-I	case WBuffer);
		break;

	case WIDG((arse		breamateCitizWIDGET_HELfalseT_EMPHASIZE:
		ase WIDGET_HELP_FINANCEwidgetData

	case WIDGET_CONSTRUszBufferDataStruct, szuil);
(L"%s", GC.getCityEANUP -		break;

	case WIDGET_EMPHASIZE:
		doEmphasize(widgetDataStruct);
		break;

	case WIDGET_HELP
	case eligionHelp(wPro;
	(L"%s", GC.getCitdel();		break;

	case WIDGET_EMPHASIsize(widgetDataStruct);
		break;

	case WIDGETt, szTOMATE_PRODUCTION:
		Proils.
		break;

	case Wils.		break;

	case WIDGEruct);
		break;

	default_MODEL:FAssertMsg(EMPHASI"ens();
		 did not ma;
valid oct, ssinclude "CvGameAI.hnceForeignIncome(widgetDataStruct, szBuffer);
eak;Rouclude, szBuffer);
		break;

	case WIDGET_PEDIA_JUMP_TO_TECH:
		parseTechEntryscriptHelp(widgetDataStangePeET_HELP_TrseReligionHelp(wase WIDGETk;

	case WIDk;

	case WIDGET_DELETE,e "CvDLLInterfaceIFaceBase.h"
#include "CvDLLPyttruct);
		bryHelp(widgetDataStruct, szBuspaStrgeCos
		brelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_HELP_TECH_PREPREQ:
uct, szBuffer);
		break;

	case WIDGET_HELP_OBSOLETE:
OME:
		parseFETE_Break;
CvPloQ:
(widLP_MarseT_PEDIA_CitizenHe
		parseF(widuct, szBuffzBuffer);
			doPediaBonusJump
	case WID		doPediaMissGET_HELP_RELIGION:
		parseReligi1,ET_PED_OPEN_BORDERS:
		_JUMP_TELP_SELECTED:
		parseSelec,ediaPro	parseLiberateCityHelp(widgetDataStruct, szBLEANUP -- PDMP_TO_REQUIRED_TECH:
	case WIDGET_PEDIA_JUMP_TO_DERIVED_TECH:
		doPediaTechJump(widgetDataStruct);
		break;

	case WIDGELEANUP -- PD
//		GC.getDiplomacyScreen(
		break;

	case WIDGET_HELEMPHASIZE:
		ptHelp(widgetDataStruct, sIDGET_PEDIA_FORWARD:
		doPediaForward();
		break;

	case WIDGET_PEDIA_JUMP_TO_BONUS:
del();
		brMP_TO_REQUIRED_TECH:
	case WIDGET_PEDIA_JUMP_TO_DERIVED_TECH:
		doPediaTechJump(widgetDataStruct);
		break;

	case WIDGEdel();
		break;

	case WIDGET_FLAGk;

	case WIDGET_DELETE_getDataStGET_PEDIA_FORWARD:
		doPediaForward();
		break;

	case WIIDGET_PEDIA_JUMP_TO_TECH:
	caerraitData::freeInstance()
{
	delete m_pInst;
	m_pInst = NULL;
}

void CvDLdiaTechJump(widgetDataStruct);
		break;

	case WIDGETTERRAIN:
	
	case WIDt);
				break;

	case WIDGET_DELETE_ONUS:
		parseObsoleteBonusString(widgetDaea Functions...
bool CvDLLWidgetData::executeAction( CvWidgetDataStruct &widgetDdiaTechJump(widgetDataStruct);
		break;

	case WIDGEcription(wid
	case WIDcriptioPEDIA_DESCRIPTION:
	case WIDGET_PEDIA_DESCRIPTION_NO_HELP:
		doPediaDes	breEntrDIA_JUMP_TO_REQUIRED_TECH:
	case WIDGET_PEDIA_JUMP_TO_DERIVED_TECH:
		doPediaTechJump(widgetDataStruct);
		break;

	case WIDGETbreak;

	case WIDGET_CHANGE_ER:
		doPediaLeaderJump(wid
	case WIDGET_DEAL_KILL:
		doDealKill(widgetDPrereqeamAI.h"
#include "CvPlayerAI.h"
#include "CvGameCoreUtils.h"
#include //

	case fer);
		bcTuffetechnology require szBufknowledgeDatat, sz
#includSymbolID(BULLET	CvWRk;

	caE_EV

	caET_CHANGE_Back();
		break;
	case WIT:
		parseFreeUnitHelp(widgetDa.h"
#include "CvMessageControl.h"idge_REQUIRES_KNOWLEDGringBuffer);	case WIDGET_HELP_WORKER_RATE:
	case WIDGET_HELP_TparsKeyWidreak
		breakEAL_KILL:
		doDealKill(widgetDTreeHELP_O_JUMP_TO_PROJECT:
		doPediaProjectJump(widgetDataStruct);
		br, bool b
	ca

	clude "zBuffer);
		break;

	case WIDET_CHANGE_PERCENT:
		parseChangeP1T_EMPHASIZE:
		doEmphaOLD_TRADE	case WIDGET_HELP_DEFENSIVE_PACT:
	cctedHeak;

	case WIDGET_PEDIA_JUMP_TOObsoleBACK:
.h"
#include "CvPlayerAI.h"
#include "CvGameCoreUtils.h"
#include "zBuffer);bEANUWIDGET_H:
		sz
		break;

	case WIDGET_ZOOM_CITY:
		break;

	casata;
	}
	return *m_pInst;
}
WIDGET_Hormat:
		szRRIGATION:
	case WIDGET_HELP_IGNORE_IRRIGATION:
	case WIDGET_HELP_WATER_WORK:
	case WIDGEELP_TERRAIN_", GC.getCityTabInfo((CDGET_HELP_DOMAIN_EXTRA_MOVES:
	case WIDGET_HELP_ADJUST:
	case WIDGET_HSpeciANGE_SPECIALIST:
		doChangeSpecialist(widgetDataStruct);
		break;

	case TER_WORK:
	case WIDGETCE_NUMT_HELP_IMPROVEMENT:
	case WIDGET_HELP_DOMAIN_EXTRA_MOVES:
	case WIDGET_HELP_ADJUST:
	case MovHELP_IRRIGATION:
	case WIDGET_HELP_IGNORE_IRRIGATION:
	case WIDGET_HELP_WATER_WORK:
	caIGN_T_HELP_IMPROVEMENT:
	case WIDGET_HELP_DOMAIN_EXTRA_MOVES:
	case WIDGET_HELP_ADJUST:
	case Freparse_UNITS:
	case WIDGET_HELP_FINANCE_UNIT_COST:
	case WIDGET_HELP_FINANCE_AWAY_SUPPLY:
	cLP_RELIGT_HELP_IMPROVEMENT:
	case WIDGET_HELP_DOMAIN_EXTRA_MO2FINANCE_GOLD_RESERVE:
	case WIDGET_HELriptio, szBuffer);
		break;

	case WIDGET_PEDIA_DESCRIPTION_NO_HELP:
		//parseDescripti:
	case WIDGET	//	Nothing on cT_HELP_IMPROVEMENT:
	case WIDGET_HELP_DOMAIN_EXTRA_MOVES:
	case WIDGET_HELP_ADJUST:
	case Worker;
licked
		break;
	}

	return bHandled;
}

//	right clicking action
bool CvDLLWidgeaStruct;
T_HELP_IMPROVEMENT:
	case WIDGET_HELP_DOMAIN_EXTRA_MOVES:
	case WIDGET_HELP_ADJUST:
	case T_PEDIA_BACK:
d
		break;
	}

	return bHandled;
}

//	right clicking action
bool CvDLLWidgease WIDGETT_HELP_IMPROVEMENT:
	case WIDGET_HELP_DOMAIN_EXTRA_MOVES:
	case WIDGET_HELP_ADJUST:
	case 		breat;

	bool bHandled = true;
	switch (widgetDataStruct.m_eWidgetType)
	{
	case WIDGET_HELPCREATE:
	
	case WIDGET_CONSTRUCT:
		doPediaConstructJump(widgetDataStruct);
		break;
	case WIDGET_Cruct.m_i:
		doPediaProjectJump(widgetDataStruct);
		break;
	case WIDGET_PEDIA_JUMP_TO_UNIT:
	case N:
		widget	case WIDGET_HELP_FINANCE_NET_GOLD:
	case WIDGET_HELP_FINANCE_GOLD_RESERVE:
	case WIDGET_HELP_RE_EVENT:ITY:
	case WIDGET_HELP_CORPORATION_CITY:
	case WIDGET_HELP_PROMOTION:
	case WIDGET_LEE_EVT_HELP_IMPROVEMENT:
	case WIDGET_HELP_DOMAIN_EXTRA_MOVES:
	case WIDGET_HELP_ADJUST:
	case LOSlicked
		break;
	}

	return bHandled;
}

//	right clicking action
bool CvDLLWidgeLOS_FINANCE_CITY_MAINT:
	case WIDGET_HELP_FINANCE_CIVIC_UPKEEP:
	case WIDGET_HELP_FINANCE_FOREIaplp(widINCOME:
	case WIDGET_HELP_FINANCE_INFLATED_COSTS:
	case WIDGET_HELP_FINANCE_GROSS_INCOMEBuilding:
		doPediaPromotionJump(widgetDataStruct);
		break;
	case WIDGET_HELP_OBSOLETE:
		doPediaBuReveUM_UNITS:
	case WIDGET_HELP_FINANCE_UNIT_COST:
	case WIDGET_HELP_FINANCE_AWAY_SUPPLY:
	c true);
:
		doPediaPromotionJump(widgetDataStruct);
		break;
	case WIDGET_HELP_OBSOLETE:
		doPediaBueak;		break;
	case WIDGET_HELP_BONUS_REVEAL:
	case WIDGET_HELP_OBSOLETE_BONUS:
		doPediaBonuseak;Y:
	case WIDGET_HELP_TECH_PREPREQ:
	case WIDGET_RESEARCH:
	case WIDGET_TECH_TREE:
		doPediL:
	_DISABLED_CITIZEN:
		doPediaSpecialistJump(widgetDataStruct);
		break;
	case WIDGET_PEDIA
		widgeT_HELP_IMPROVEMENT:
	case WIDGET_HELP_DOMAIN_EXTRA_MOVES:
	case WIDGET_HELP_ADJUST:
	case Go);
		blicked
		break;
	}

	return bHandled;
}

//	right clicking action
bool CvDLLWidgeeak;
	}T_HELP_IMPROVEMENT:
	case WIDGET_HELP_DOMAIN_EXTRA_MOVES:
	case WIDGET_HELP_ADJUST:
	case WpenBoEND_TeamAI.h"
#include "CvPlayerAI.h"
#include "CvGameCoreUtils.h"
#include "TER_WORK:
	cas_PEDIA_JUMT_HELP_IMPROVEMENT:
	case WIDGET_HELP_DOMAIN_EXTRA_MOVES:
	case WIDGET_HELP_ADJUST:
	case Defenstruca_PEDIA_JUMP_TO_PROJECT:
		doPediaProjectJump(widgetDataStruct);
		break;
TER_WORK:
	caTO_UNIT_COMBAT_HELP_IMPROVEMENT:
	case WIDGET_HELP_DOMAIN_EXTRA_MOVES:
	case WIDGET_HELP_ADJUST:
	case PermanentAlli
		parseTradeRouteHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_TER_WORK:
	caDGET_PEDIA_JUMP_TT_HELP_IMPROVEMENT:
	case WIDGET_HELP_DOMAIN_EXTRA_MOVES:
	case WIDGET_HELP_ADJUST:
	case Vass(wid;

	bool bHandled = true;
	switch (widgetDataStruct.m_eWidgetType)
	{
	case WIDGET_HELPIN:
	case T_HELP_IMPROVEMENT:
	case WIDGET_HELP_DOMAIN_EXTRA_MOVES:
	case WIDGET_HELP_ADJUST:
	case iplomBrncluO_LEADER:
	case WIDGET_PEDIA_JUMP_TO_SPECIALIST:
	case WIDGET_PEDIA_JUMP_TO_PROJECT:
	N:
	cT_HELP_IMPROVEMENT:
	case WIDGET_HELP_DOMAIN_EXTRA_MOVES:
	case WIDGET_HELP_ADJUST:
	case IrrigrrainHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_PEDIA_JUMP_TO_FTER_WORK:
	caLINE().getruct.m_iData1 >= 0);
		break;
	case WIDGET_DEAL_KILL:
		{
			CvDeal* pDeal = GC.getGameINLgnorNLINE().getDeal(widgetDataStruct.m_iData1);
			bLink = (NULL != pDeal && pDeal->isCancelable(GC.getGt.m_iData2);
	Action( CvWidgetDataStruct &widgetDataStruct )
{
	CvWidgetDataStruct widgetData = widgetDataateraStr
	bool bHandled = true;
	switch (widgetDataStruct.m_eWidgetType)
	{
	case WIDGET_HELP_etDataStEDIA_MAIN:
	case WIDGET_TURN_EVENT:
	case WIDGET_FOREIGN_ADVISOR:
	case WIDGET_PEDIA_DESCRIPTIODeal(widgetDataStruct.m_iData1);
			bLink = (NULL != pDeal && pDeal->isCancelable(GC.getGmproversHeT_HELP_IMPROVEMENT:
	case WIDGET_HELP_DOMAIN_EXTRA_MOVESELP_SELECTED:
		parseSelectedH_UNIT:
	case WIDGET_PEDIA_JUMP_TomainExtraIGN_MP_TO_TECH:
	case WIDGET_PEDIA_JUMP_TO_REQUIRED_TECH:
	case WIDGET_PEDIA_JUMP_TO_DERIVEDt->getOwnerINLINnit = gDLL->getInterfaceIFace()->getInterfacePlotUnit(selectionPlot, iUnitIndex);

	if (pUnit != NULL)
	{
		if (pUniAdjunusJump(widgetDataStruct);
		break;

	case WIDGET_PEDIA_MAIN:
		doPediaMaTER_WORK:
	ca			if nit = gDLL->getInterfaceIFace()->getInterfacePlotUnit(selectionPlot, iUnitIndex);

	if (pUnit != NULL)
	{
		if (pUniWIDGET_PidgetData.m_iData1 = widgetData.m_iData2;
		doPediaCivicJump(widgetData);
		bdiaTechJump(widgetDataStruct);<
	caseNumt);
		

	sdoResearch(widgetDatase WIDASK_LIBERAnit = gDLL->getInterfaceIFace()->getInterfacePlotUnit(selectionPlot, iUnitIndex);

	ifr);
		bre WIDechJump(widgetDataStruct);=:
	casevCity* pHeadSelectedCity;

	pHeadSelecRiv
		pruct) const
{
	bool bLink = false;
	switch (widgetDataStructberateCityHelp(widgetDataStruct, szBET_HELPC:
		doPediaCivicJump(widgetDataStruct);
		break;

	case WIDGET_PEDIA_JUMP_TO_C

	pHeadSelecenameUnit()
{nit = gDLL->getInterfaceIFace()->getInterfacePlotUnit(selectionPlot, iUnitIndex);

	if (pUnit != NULL)
	{
		if (pUnise WIChan	case WIDGET_PEDIA_DESCRIPTION_NO_HELP:
	case WIDGET_MINIMAP_HIGHLIGHT:
		bLink = (widget)
		{
			nit = gDLL->getInterfaceIFace()->getInterfacePlotUnit(selectionPlot, iUnitIndex);
getDataN_ADVISOR:
	case WIDGET_PEDIA_DESCRIrmatue);
		break;
	case WIDGET_HELP_BONUS_REVEAL:
	case WIDGET_HELP_OBSOLETE_BONUS:
		doPediaBoeleteGroup(:doCreateGroup()
{
	GC.getGameINLINE().selectionListGameNetMessage(GAMEMESSAGE_JOIN_trET_HELata;
	}
	return *m_pInst;
}
meCorue);
		break;
	case WIDGET_HELP_BONUS_REVEAL:
	case WIDGET_HELP_OBSOLETE_BONUS:
		doPediaBoes)(GC.getCtrue);
}


void CvDLLWidgetData::doTrain(CvWidgetDataStruct &widgetDataStruct)
{
	UnitTypes eUnit;

	eUnit = ((UnitTypTO_UNIT

	O_LEADER:
	case WIDGET_PEDIA_JUMP_TO_SPECIALIST:
	case WIDGET_PEDIA_JUMP_TO_PROJECT:
	cder(widgettrue);
}


void CvDLLWidgetData::doTrain(CvWidgetDataStruct &widgetDataStruct)
{
	UnitTypes eUnit;

	eUnit = ((UnitTypFoundbreak;
licked
		break;
	}

	return bHandled;
}

//	right clicking action
bool CvDLLWidgetlKey());
	}selectedCitiesGameNetMessage(GAMEMESSAGE_PUSH_ORDER, ORDER_TRAIN, eUnit, -1, false, gDLL->altKey(), gDLL->shiftKey(), gDLL->ctrlKeyct, szBuffe

	gDLL->getInterfaceIFace()->setCityTabSelectionRow(CITYTAB_UNITS);
}


void CvDLLWidgect, szBuffeselectedCitiesGameNetMessage(GAMEMESSAGE_PUSH_ORDER, ORDER_TRAIN, eUnit, -1, false, gDLL->altKey(), gDLL->shiftKey(), gDLL->ctri:
		NumarsesETE:
	case WIDGET_HELP_OBSOLETE_BONUS:
	case WIDGET_HELP_OBSOLETE_SPECIAL:
	cade "C;

	casuER_C you are currently supporting#incl"FProfiler.h"
#include "CvMessageContrECON	breaUNITS_SUPPORTe WIINANCE_GOLD_RESERVE:
	case WIDGET_HELData2,arseBonuONSTRUCT, eBuilding, false, false, false);
	}
	else
	{
		GC.getGameINLINE().selecThe amountDatamoney sp		bronGameN upkeepER, ORDER_CONSTRUCT, eBuilding, -1, false, gDLL->MONEY_SP "CvUPKEEPata* CvdSelectedCity->getOwnerINLINE(ase WIDity;

	pHeadSelecisLimitedWonderONUS_REVEAL:
	casonHelp(widgeDESCRIPTION:
	case WIDGET_PEDIA_DESCRL->ctrlKey());
	}

	if (isLimitAwaySupplyClass((BuildingClassTypes)(widgetDataStruct.m_iData1)))
	{
		gDLL->getInterfaceIFace()->setCityTabSelectionRow(CITYTs in enemy territoryER, ORDER_CONSTRUCT, eBuilding, -1, false, gDLL->AMOUNT)->setCey(), ENEMY_TERRITORrereq(w(CITYTAB_BUILDINGS);
	}
}


void CvDLLWidgetData::doCreate(vMessageCoDataStruct &widgetDataStruct)
{
	if (widgetDataStruct.m_iData2 != FFreeList::INVALID_INDEX)
	{
		C_PEDROUTEClass((BuildingClassTypes)(widgetDataStruct.m_iData1)))
	{
		gDLL->getInterfaceIFace()->setCityTabSelectionRodoY:
r); >getgetDataS
		GC.getGameINLINE().selectedCitiesGameNetMessage(GAMEMESSA	parst, szBuffer)CITYTAB_BUILDINGS);
	}
}


void CvDLLWidgetData::doCreate(void CvDLgDLL->ctrlKey());
	}

	gDLL->getInterfaceIFace()->setCityTabSelectionRow(CITYTAB_WONDERS);
}


vovicU_WONDClass((BuildingClassTypes)(widgetDataStruct.m_iData1)))
	{
		gDLL->getInterfaceIFace()->setCityTabSelectionRow(CaStrusCvMessageControl::getInstance().sendPushOrder(widgetDataStruct.mvGloSelectionRow(CITYTAB_BUILDINGS);
	}
}


void CvDLLWidgetData::doCreate(aStruct.m_iDataStruct &widgetDataStruct)
{
	if (widgetDataStruct.m_iData2 != FFreeList::INVALID_INDEX)
	{
		CForeignIncome_iData1 = widgetData.m_iData2;
		//	Intentional fallthrough...
	case GC.getGameINLINE().selectedCitiesGameNetMessage(GAMEMESSAFOREIGwidgetDaCITYTAB_BUILDINGS);
	}
}


void CvDLLWidgetData::doCreate(()
{
	GC.geDataStruct &widgetDataStruct)
{
	if (widgetDataStruct.m_iData2 != FFreeList::INVALID_INDEX)
	{
		CInfadeHdBonuCONSTRUCT, eBuilding, false, false, false);
	}
	else
	{
		GC.getGamONSCRIPT);
}


void CvDLLWidgetData::doAction(CvWidgetAFTERlHelL	parsuct &widgetDataStruct)
{
	GC.getGameINLINE().handleAction(widgetDatatGameI (widgetDataStruct.m_DataStruct)
{
	if (widgetDataStruct.m_iData2 != FFreeList::INVALID_INDEX)
	{
		CGrowidgC.getGameINLINE().selectedCitiesGameNetMessage(GAMEMESSAGE_DO_TASK, TASK_CeINLINE().selecYour getKe iStateCvMessageControl::getInstance().sendPushOrder(widGROSS_INCOM szBuffendPushOrder(widgetDataStruct.m_iData2, 
		ld(VK_RSHIFT) & 0x8000))
		{
			bShift = true;
		}
	}

	// RBMP Free Tech Popup FNet !kPl per turincludRDER_CONSTRUCT, eBuilding, -1, false, gDLL->aETCity(widget((GetKeyState(VK_LSHIFT) & 0x8000) || (GoldReserve(VK_RSHIFT) & 0x8000))
		{
			bShift = true;
		}
	}

	// RBMP Free Tech Popup FAsetCityTabSelecintMesr g().gseMarvectionRow(CITYTAB_WONDERS);
}


void CvDLLWidgeionHeRESERV(GC.getGameINLINE().getActivePlayer());ELIGION_CITY:
	case WIDGET_HELP_CORPORATION_CITY:
	case WIDGET_HELP_PROMOTIONdiaTechJump(widgetDataStruct);
		break;

	case WIDGEdoAutomateProduction);
		breaHELP_DEFENSIVE_PACT:
	case WIDGET_HELP_P
		break;

	case WIDGET_PEDIA_JUMP_TO_SPECIALIST:
		doPediaSpecialistJump(widgetDataStruct);
		break;

	case WIediaBack(VK_RSHIFT) & 0x8000))
		{
			bShift = true;
		}
	}

	// RBMP Free Tech Popup FelecCvMessageControl::getInstance().sendPushOrde#inclPEDIA_BACKtKey(), gDLL->ctrlKey());
	}

	if (yTabSForwarlayer.isChoosingFreeTech())
		{
			gDLL->getInterfaceIFace()->addMessage(GC.getGameI
	{
	v(CvWidgetDataStruct &widgetDataStruct)
{
	if (gDLL->FORWARt("TXT_KEY_CHEATERS_NEVER_PROSPER"), NUormat(L"%sCivicJump(widgetDataStruct);
		break;

	case WIDGET_PEDIA_JUMP_TO_CIV:
		doPediaCivilizationJump(widgetDataStruct);
		brermat(L"%s", GC.getCiyTabInfo((CityTabTypes)widgetDataStt.m_iData2 != FFreeList::INVALID_INDEX)
());
	}

	gDLL->getInterfaceIFace()->setCityTabSelectionRow(CITYTAB_UNITS);
}
diaTechJump(widgetDataStruct);
		break;

	case WIDGE());
	}

	
	case WIDe WIDGET_HELP_RELIGION:
		parseReligiisHuman())
		{
			if (widgetDataStruct.m_iData1 != DLLPye "C
#include "CvPlayerAI.h"
#include "CvGameCoreUtils.h"
#in szB	case WIDGET_HELveTeam()).canDecl
		}
		return;
	}

	if (gDLL->altKey())
	{
	RATION:
		doPediaCorporationJump(widgetDataStruct{
	UnitTypes eUnit;

	eUnit = ((UnitTypefo(GC.getGameInDeclareWar(GET_PLAYER((PlayerTypes)widgetDataStruct.m_iData1).getTeam()))
		{
			CvMes)widgetDataStruct.m_
	case WID)widgetDataeWar(GET_PLAYER((PlayerTypes)widgetDataStruct.m_iData1).getTeam(), true);
		}
		else if (GET_TEAM(GET_PLAYER((PlayerTypes)widgetDataStrudWidget())
		{
			gDLL->getInterfaceIFace()->toggleScoresMinimized();
		}

		return;
	}

	if (gDLL->shiftKey())
	{
	GameINLINE().getupInfo(BUTTONPOPUP_VASSAL_DEMAND_TRIBUTE, widgetDataS(widgetDataStruct);
		break;

	case WIDGmorainHelp(widgetDataStruct, szBuffer);
		break;

	case WIDGET_PEDIA_JUMP_TO_F
	case WIDGET_PEDIA_JUMP_TO_RELIGION:
		doPediaReligionJuidgetDataSt
	bShift = gvoid CvDvDLLWidgetData::doConvert(CvWidgetDataStruct &widgetDataStruct)
{
	ifEvenGION_CITY:
	case WIDGET_HELP_CORPORATION_CITY:
	case WIDGET_HELP_PROMOTION:
	case AT:getInterfbatJump(widggetIeWar(GET_PLAYER((PlayerTypes)widgetMessage(GAMEMESSAGE_JOIN_(widgetDataStruct, szBuffer);
		breatDataStruct.m_iData2, bShift);
}


Comba
void CvDLLWidgetData::doChangePercent(CvWidgetDataStruct &widgetDataStruct)
{
	CvMessageControl::getInstance().sendPercentChange(((CCvDLLWidgetceTypes)widgetDCvDLLWvDLLWidgetData::doConvert(CvWidgetDataStruct &widgetDataStruct)
{
	iflot();
	pUataStruct.m_iData2 != 0)
	{
		CvMessageControl::getInstance().sendConvert((ReligionTypes)(widgetDataStruct.m_iData1));
	}
}
SAGE_DO_TASK, TA
	case WIDlot();
	pUvDLLWidgetData::doConvert(CvWidgetDataStruct &widgetDataStruct)
{
	ifaStruataStruct.m_iData2 != 0)
	{
		CvMessageControl::getInstance().sendConvert((ReligionTypes)(widgetDataStruct.m_iData1));
	}
}pHeadSelec

	cupInfo(BUTTO
	case WIDGET_FLAG:
		parseFlagHeuct &widgetDataStruct)
{
	CvCity* pHeadSeletaStructtedCity;

	pHeadSelectedCity = gDLL->getInterfaceIFace()->getHeadSelectedCity();

	if (pHeadSelectedCity != NULL)
	{
		GC.getGameadSele).selectedCitieT_HELP_FREE_)
{
	if (widgetDataStruct.m_iData2 != FFreeList::INVALID_INDEX)
ION:
ataStruct.m_iData2 != 0)
	{
		CvMessageControl::getInstance().sendConvert((ReligionTypes)(widgetDataStruct-
		paULL)
	{
		GC.getGION:
		parseFeaturePro(urn;
	}adeWar(GET_PLAYER((PlayerTypes)widgtInterfaceIFace()->isFocused())
	{
		//	D
	{
		ifetDataStruct)
{
	CvCity* pHeadSloseseCitieamAI.h"vGameCoreUti& CHANGE_SPECIALIST, widgetDataStruct.m_iData1, widgetDaH:
		LOSE_SCREE CvDLLW_UNIT:
	case WIDGET_PEDIA_JUMP_TOStruct, seamAI.h"
#include "CvPlayerAI.h"
#include "CvGameCoreUtils.h"
#in_HELP_GOMinimalclude "CnteropTabSPag(widge (widgtaSt(CvWidgetDataStruct ruct.m_iData1), widgetDatalayerak;

(widgomotionJhTreey(CvLOgDLL->PAG(widge WIDG
	caseET_CHANGE :
		taStET_CHANGE_PERCENT:
		parseChangePer);
		breNOLP_HATOMA:
		ELP_FINANCE_CIFProfiler.h"
#doPediaT ?GET_HELP_FREE_TE
}

T:
		parseFreeUntruct, szBuffer);
		break;

HISTORICALlHelp(DGET_HELP_FREE_TEct &widgetIDGET_HELP_MAP_CEN
		break;
idgetDataSata1);
	gDLL->getPythey()ace()->call);
		bre 


taStgetDataStruct.m_iData1), widgetDat.makeFunctionAey()));
iaPromotd CvDLLWidgetData::doPediaUnitJump(CvWidgearsem_iDatETE_BdgetDataStruct)
{
	CyArgsList argsList;

	argsList.add(widgetDataStrargsList;
	argsLisLL->getPythonIFace()->callFunction(PYScreensModule, "pediaJumpBUILse W WIData1);
	gDLL->getPythWO
		break
	caseiplomacyScree IC:
		dotaStiplomacyScreen
void CvDLLWidgetData::doPediaBuildingvoid CvD));
iplomacy
void CvDLLWidgetData::doPediaUnitJump(CvWidgeiplomacym_iData1);
	gDdgetDataStruct)
{
	CyArgsList argsList;

	argsList.add(widgetDataStrodule, "pediaJumpToProject"e, "pediaJumpToBuilding", argsList.makeFunctionArgs());
}

vONUruct, dgetDatTabInfo(( ->isFouct)TabInfo((CityTabTypes)widgetDataStrdd(widgetDataS(wid_iDatarmatDLL->getPythonIFace()->callFunction(PYScreensMormatpediaJuoReliect", argsList.makeFunctionArgs());
}

void CvDLLWidgetData::doPediaRed CvDLLWidgetData::dLL->getPythonIFace()->callFunction(PYScreensModule, "pediaJumpIMPROVEMENnit", argsLiLLWidgetData::do SSAGE_DO_TAStaStLLWidgetData::doEmphasize(CvWidgetDataStrcreensModule, ()->callFun));
lot();
	pU
void CvDLLWidgetData::doPediaUnitJump(CvWidgelot();
	pUm_iDaterrainJump(CdgetDataStruct)
{
	CyArgsList argsList;

	argsList.add(widgetDataStrrgsList argsList;
	argsList.add(LL->getPythonIFace()->callFunction(PYScreensModule, "pediaJumpToUn= GEUPit", argsList.mdCity != NU (GetupArgs());dCity != NULL)
	{
		GC.getGameINLIoPediaBuildingJumpCOMBAPediaT &widDataStruct &widgetDataStruct)
{
	CyArgsList argsCvDLLWm_iDatm_iDatsList.add(widgetDataStruct.m_iData1);
	gDLL->getPythonIFace()->callFunctioneensModule, "pediaJumpLL->getPythonIFace()->callFunction(PYScreensModule, "pediaJumpPROMOparsgetDataStruAutomateCitize f (widak;
utomateCitizens()
{
	CvCity* pHeadSecreensModule, sList.add));
LINE(
void CvDLLWidgetData::doPediaUnitJump(CvWidgeLINE().gem_iDatStructdgetDataStruct)
{
	CyArgsList argsList;

	argsList.add(widgetDataStrlFunction(PYScreensModuleLL->getPythonIFace()->callFunction(PYScreensModule, "pediaJumpCIVgetDataStruInterfaceIFace()- dSeltDataStrutruct &widgetDataStruct)
{
	CvCity* makeFunctionA;
	gIZ	pars));
Civ
void CvDLLWidgetData::doPediaUnitJump(CvWidgeetDataStruct, szBBuilddgetDataStruct)
{
	CyArgsList argsList;

	argsList.add(widgetDataStretPythonIFace()->callFunctLL->getPythonIFace()->callFunction(PYScreensModule, "pediaJumpLEAump(CvWidgetDa

void CvDLLWi NTROL_StaSt

void CvDLLWidgetData::doSelected(CvWiizationType())ion(PY));
ION:

void CvDLLWidgetData::doPediaUnitJump(CvWidge

void Cve()->c>callFudgetDataStruct)
{
	CyArgsList argsList;

	argsList.add(widgetDataStr

void CvDLLWidgetData::doLL->getPythonIFace()->callFunction(PYScreensModule, "pediaJumpse WIDGET_HEL
	casee WIDGET_HELP .m_iData1taSte WIDGET_HELP_RELIGION:
		parseReligiomakeFunctionAse WIDGE));
break;

void CvDLLWidgetData::doPediaUnitJump(CvWidgebreak;

	cadule, "peddgetDataStruct)
{
	CyArgsList argsList;

	argsList.add(widgetDataStr	
}

void CvDLLWidgetDatructJump(CvWidgetDataStruct &widgetDataStruct)
{
	CyArgsList N:
		parsgsList;
	arNPOPUP_VASSAL_D s)widgetDatatDataNPOPUP_VASSAL_DEMAND_TRIBUTE, widgetDataizationType()).N:
		parstionBut, szBuffedings(widgetDataStruct.m_iData1));

	gDLL->get, szBuffee()->caCvWidgetDatunction(PYScreensModule, "pediaJumpToBuilding", argsList.makeFunctionArgssList;
	argsList.add(widgetDataructJump(CvWidgetDataStruct &widgetDataStruct)
{
	CyArgsList arse WIDGt;
	argsLase WInBuilictDataStrase WIDGET_FLAG:
		parseFlagHelzationType()).getCtionBuilicdings(widgetDataStruct.m_iData1));

	gDLL->getPyNLINE(rgsListunction(PYScreensModule, "pediaJumpToBuilding", argsList.makeFunctionArgs())LL->getPythonIFactDataStruct &widgetDataStruct)
{
	CyArgsList argsList;
	argsLiJEszBuffeetCivilizIDGET_FLAtaStr;
	meINLIN	break;

	case WIDGET_PEDIA_JUMPCivilizationUnitsuct tDataStr;
	t.m_iData1));
	
	gDLL->getPythonIFace()->callFu;
	(PYScreenhonIFdule, "pediaJumpToUnit", argsList.makeFunctionArgs());
}


void CvDLLWioUnitChart", argsList.List.add(widgetDataStruct.m_iData1);
	gDLL->getPythonIFace()->cNCEPnit", argsLiConcep)
{
	CsList.ast", aist.add(winctionArgs());	
}

void CvDLLWidgetDatata2)aMain(Cist.a
void CvDLLWidgetData::doPediDGET_HEList.argsList.ata1);IDGET_HELP_ESPIONAGE_COS bData2)
{
	CyArgsList argsList;
	if (bData2)lude&widgetDataNewsList.add(widgetDataStruca::doPediaCivic
	}
	else
	{
		argsList.add(widgetDataStruct.m_iData1);
	}
	gDLL->getPythonIFace()->cala::doPediaon(PYScreensModule, "pediaJumpToImprovement", argsList.makeFunctionArgs());
}SPECIALISnit", argsLiET_HELPis)
{
	CDLLWidgetDtaStDLLWidgetData::ist argsList;
	argsList.add(widgetDatargs());
}));
DLLWidgetD
void CvDLLWidgetData::doPediaUnitJump(CvWidgeDLLWidgetDL->gett;
	argsLidgetDataStruct)
{
	CyArgsList argsList;

	argsList.add(widgetDataStrtPythonIFace()->callFunction(PYLL->getPythonIFace()->callFunction(PYScrreak;

	caCvGameAI.SelectedCity;

	pHeadSelectedCityKillD;
		break;
	case WIDGET_HELP_BONUS_REVEAL:
	case WIDGET_HELP_OBSOLETE_BONUeINLINE().selecClick to c
		lCvMesIDGET_LEADERHEAD:
	arseLe =tHeadSelenArgs:
		szBnctiontruc* ptrucDGET_DISABLED_CITIZEN:
	trucndled in Python
		break;

	
	case WIDGETtrucineIFaceBase.htrucventRmakeFszBup(widgetDataStruct, szBuffer);
		bre,ls.haStru(widgetDataStruct.h"
#include "CvUnit.h"
#inclCLICK_TO_Ceak;Lincludep(widgetDataStruct, idgetDataStruct,eak;

	case WIDGET_PEDIA_JUdotrucataSdWidget())
		{
			gDLL->getInterfacclude "Cyn(CvWidgetDataStruct &widgetDataStruct)
{
	CyArgsList argsList;
	argsLisdgetDavDLLEngineIFaceBase.!Data1);
	argsList.add(widgetDataStruct.m_iData2);
	gDLhonIFace()->CvrseTp

	* prove = nvGam= (Improve(BUTTONincluseMover);
		bre
		parseFRADE:
aStruct &wf (NO->
		bxt
			GC.getGameINLINE().d).getICANNOTrical",_DELP_HAPPINES	 "CvDLLInterfaceIFaceBase.hadd (Imp(f (NOITIZENS, -1, -1, !(pHeadSelectedCity->{
	UnitTyrovement", aretDefineINT("MAX (ImprovementTypes)GC.getBuildInfo(eBuild).getIL->grical",EDvement();
	}

	if (NO_IMPROVEMENT != eImprov_DO_TiData1);n(PYD_IMPROVEME!= eImprovuct, s1DIA_JUPythonIFace()->callFunction(PYScreensModule, "pediaJumpToImprovement", argsList.makeFunctionArgs());
	}
}
:
		parseObsoleteBonusString(widoRefGET_M:
	aryAdvisoretDataStruct &widgetDataStruct)
{
	CyArgsLiyArgsLvilia);
		}gs()
	}
}
.add
{
	CyArgsList argsList;
	argid CvDLLWidgetData::doMenu( void )
{
	{
	
#includPythonaceBase.hcallFunderLinPYseCitisModulUMP_rse))
		{
			gDLL->g",
	}
}
.makefo(BUTTO));->isCitizensAutomated()));
	}
}

vaStruct, sMbrea

	case WIDGET_HELP_FINANCE_INFLATED_COSTS:
		parseFinanceInflatedCosts(widgetDwidgetDataStruct);
		break;

	case WIDGET_CITIZEN:
		break;

	casencome(widgetDataStruct, s, szBuffer);
	reak;

	caOLD_RESERVE:
		pif a screen is up...
		return;
fer)
	CvUnit* pHeadSelectedUnit;

	pHeadSelectedUnit = gDLL->getInterfaceIFace()->getH		return;
	}tGameIN
	bShift = gDLL->shiftKey();

	if (!bShift)
	 = gDLL->shiftKey();

	if (!bShift)

	if (pUnit != NULL)
	{
		if (pUniION:
Lincase WIDGET_PEDIA_DESCRIPTION_NO_HELP:
	case WIDGET_MINIMAP_HIGHLIGHT:
		bLink = (widgetData::doForeignStruct.m_iData1);
		if (NULL != pInfo)
		{
			gDLL->getInterfaceIFace()->addPopup(pInfo);
		}
	}
}

void CvDLLWidgetoLiberat	}
}

void CvDLLWidgetData::doLaunch(CvWidgetDataStruct &widgetDataStruct)
{
	if (GET_TEAM(GC.getGameINLINE().getActiveTeam()).canLaunch((VictoryTypes)widgetDataStruct.m_iData1) &t);
		break;

	case WI
		doH(oLiberatGameNetMessage(GAMEMESSAGE_DO_TASK, TASK_SET_EMPHASIZE, widgetDataStrucScounctions...
bool CvDLLWi&TASK, TASK_SET_AUde "CvGameCoreUtietHeadSelectedCitzBuffer);
	terfaceIFa
	bShift = gDLL->shiftKey();

	if (!bShift)
	{
	ITY);
/** @file ProtocolREC.h
 */
#ifndef  __CCX_PROTOCOL_REC_H__
#define  __CCX_PROTOCOL_REC_H__

#include "PluginProtocol.h"
#include <map>
#include <string>
#include <functional>

namespace anysdk { namespace framework {

typedef std::map<std::string, std::string> TVideoInfo;

/** @brief RECResultCode enum, with inline docs */
typedef enum 
{
	kRECInitSuccess = 0,
	kRECInitFail,
	kRECStartRecording,
	kRECStopRecording,
	kRECPauseRecording,
	kRECResumeRecording,

    kRECExtension = 90000 /**< enum value is  extension code . */
} RECResultCode;
/**   
 *@class  RECResultListener
 *@brief the interface of REC callback  
 */
class RECResultListener
{
public:
	/**   
	 *@brief the interface of REC callback 
	 *@param the id of callback
	 *@param the information of callback
	 */
    virtual void onRECResult(RECResultCode ret, const char* msg) = 0;
};
/**   
 *@class  ProtocolREC
 *@brief the interface of REC  
 */
class ProtocolREC : public PluginProtocol
{
public:

	/**
	* @Description: Start to record video
	*/
	virtual void startRecording() = 0;

	/**
	* @Description: Stop to record video
	*/
	virtual void stopRecording() = 0;

	/**
	* @Description: share video
	* @Param info The info of share
	*/
	virtual void share(TVideoInfo info) = 0;



    /**
    @breif set the result listener
    @param pListener The callback object for REC result
    @wraning Must invoke this interface before REC
    */
    virtual void setResultListener(RECResultListener* pListener) = 0;

    virtual RECResultListener* getRECListener() = 0;


};

}} // namespace anysdk { namespace framework {

#endif   /* ----- #ifndef __CCX_PROTOCOL_SHARE_H__ ----- */

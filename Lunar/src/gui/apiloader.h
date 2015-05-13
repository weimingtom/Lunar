#ifndef GUI_APILOADER_H
#define GUI_APILOADER_H

#include <vector>
#include <set>
#include <QtCore/QObject>
#include <QThread>
#include "util/base.hpp"
#include "util/luaextend.hpp"

namespace gui
{

class ApiLoader;

class ApiLoadThread : public QThread
{
    Q_OBJECT

    enum LoadApiType
    {
        Unknown,
        CommonApi,
        SupplementApi
    };

public:
    ApiLoadThread(ApiLoader* papi_loader, QObject *parent = 0);
    virtual ~ApiLoadThread();
    void startLoadCommonApi(const std::string& api_dirs);
    void startRefreshSupplementApi(const std::string& parse_supplement_api_script, const std::string& parse_supplement_api_func);
signals:
    void loadFinish(bool, const QString&);
protected:
    virtual void run();
private slots:
    void onLoadFinish(bool result, const QString& error_info);
private:
    std::string api_dirs_;
    std::string parse_supplement_api_script_;
    std::string parse_supplement_api_func_;
    ApiLoader* papi_loader_;
    LoadApiType load_api_type_;
    bool loading_;
};

class QsciAPIsEx;
class ClassInfo;

class ApiLoader
{
public:
    friend class ApiLoadThread;

    ApiLoader(QsciAPIsEx* papis,
              const std::string& file);
    ~ApiLoader();

    void loadCommonApiAsync(const std::string& api_dirs);
    void loadSupplementApiAsync(const std::string& parse_supplement_api_script, const std::string& parse_supplement_api_func);
    inline std::string errorInformation() const { return error_information_; }
private:
    bool initLuaState(const std::string& parse_supplement_api_script);
    void loadCommonApi(const std::string& api_dirs);
    std::pair<bool, std::string> refreshSupplementApi(const std::string& parse_supplement_api_script, const std::string& parse_supplement_api_func);
    bool parseSupplementApi(const std::string& parse_supplement_api_func);
    bool appendSupplementApi(const std::string& parse_supplement_api_script, const std::string& parse_supplement_api_func);
    void clearSupplementApi();
    void prepare();
private:
    ApiLoadThread api_load_thread_;
    QsciAPIsEx* papis_;
    std::string file_;
    std::set<std::string> api_supplement_;
    util::LuaState lua_state_;
    bool lua_state_ok_;
    std::string error_information_;
private:
    DISALLOW_COPY_AND_ASSIGN(ApiLoader)
};

} // namespace gui



#endif // GUI_TMPAPILOADER_H

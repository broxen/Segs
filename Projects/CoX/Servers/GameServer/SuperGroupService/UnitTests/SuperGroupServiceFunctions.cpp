#include "Servers/HandlerLocator.h"

#include "SuperGroupHandler.h"
#include "SuperGroupHandlerEvents.h"
#include "InternalEvents.h"
#include "MessageBus.h"
#include "SEGSEventFactory.h"

#include <QTest>

using namespace SEGSEvents;
struct MockEventProcessor : public EventProcessor
{
    std::unordered_map<uint32_t,Event *> m_mocked_responses;
    IMPL_ID(MockEventProcessor)
    bool hasNoMessages()
    {
        return this->msg_queue()->message_count()==0;
    }
    // EventProcessor interface
protected:
    void dispatch(Event *) override { QVERIFY(false); }
    void serialize_from(std::istream &) override { QVERIFY(false); }
    void serialize_to(std::ostream &) override { QVERIFY(false); }
};

extern void register_SuperGroupHandlerEvents();
void        sendMessages(EventSrc *tgt, std::initializer_list<Event *> msgs)
{
    for (auto *msg : msgs)
        tgt->putq(msg);
}
uint32_t createMockChar()
{
    static uint32_t char_id=1;
    //assert(false);
    return char_id++;
}
class SuperGroupServiceFunctions : public QObject
{
    Q_OBJECT
    uint32_t            m_bound_game_server=0;
    uint32_t            mock_char_id_A=0;
    uint32_t            mock_char_id_B=0;
    uint32_t            mock_char_id_C=0;
    MockEventProcessor *m_mock_game_server = nullptr;
    MockEventProcessor *m_mock_map_server = nullptr;
    MockEventProcessor *m_mock_game_db_server = nullptr;
    MessageBus          m_message_bus;
    void simulateUserComingOnline(SuperGroupHandler* tgt,uint32_t user_id,const vSuperGroupRoster &memberlist)
    {
       tgt->putq(new ClientConnectedMessage({0,m_bound_game_server,0, user_id },0));
       tgt->putq(new SGMemberConnectedMessage({0,m_bound_game_server,0, user_id, memberlist},0));
    }
    void processAllMessages(SuperGroupHandler *tgt, int limit = 10)
    {
        // process all messages to completion
        bool completed = false;
        for (int i = 0; i < limit; ++i) {
            completed |= tgt->process_single_event() == 0;
            if(completed)
                break;
        }
        QVERIFY(completed);
    }
private slots:
    void initTestCase()
    {
        register_SuperGroupHandlerEvents();
        HandlerLocator::setMessageBus(&m_message_bus);
        // createMockGameHandler();
        mock_char_id_A     = createMockChar();
        mock_char_id_B     = createMockChar();
        mock_char_id_C     = createMockChar();
        m_mock_game_server = new MockEventProcessor;
        m_mock_game_db_server = new MockEventProcessor;
        m_mock_map_server = new MockEventProcessor;
        HandlerLocator::setGame_Handler(0, m_mock_game_server);
        HandlerLocator::setMapInstance_Handler(0,0, m_mock_map_server);
        HandlerLocator::setGame_DB_Handler(0,m_mock_game_db_server);
    }
    void connectedUserWithoutFriendsWillNotPostAnyMessages()
    {
        SuperGroupHandler sg(0);
        simulateUserComingOnline(&sg,mock_char_id_A,{});
        processAllMessages(&sg,10);
        QVERIFY(m_mock_game_server->hasNoMessages());
        QVERIFY(m_mock_game_db_server->hasNoMessages());
        QVERIFY(m_mock_map_server->hasNoMessages());
    }
    void addingAndRemovingSame()
    {
        SuperGroupHandler sg(0);
        sendMessages(&sg, {
                                    new SGMemberAddedMessage({mock_char_id_A, mock_char_id_B, {}}, 0),
                                    new SGMemberRemovedMessage({mock_char_id_A, mock_char_id_B}, 0),
                                });
        processAllMessages(&sg,10);
        // todo: verify that mock_char_id_A and mock_char_id_B are no longer friends.
        QVERIFY(false);
    }
};

QTEST_MAIN(SuperGroupServiceFunctions)

#include "SuperGroupServiceFunctions.moc"

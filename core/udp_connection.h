#pragma once

#include <string>
#include <mutex>
#include <thread>
#include <atomic>
#include "connection.h"

namespace dronecode_sdk {

class UdpConnection : public Connection {
public:
    explicit UdpConnection(Connection::receiver_callback_t receiver_callback,
                           const std::string &local_ip,
                           int local_port);
    ~UdpConnection();
    ConnectionResult start();
    ConnectionResult stop();

    bool send_message(const mavlink_message_t &message);

    // Non-copyable
    UdpConnection(const UdpConnection &) = delete;
    const UdpConnection &operator=(const UdpConnection &) = delete;

private:
    ConnectionResult setup_port();
    void start_recv_thread();

    void receive();

    std::string _local_ip;
    int _local_port_number;

    std::mutex _remote_mutex{};
    std::string _remote_ip{};
    int _remote_port_number{0};

    int _socket_fd{-1};
    std::thread *_recv_thread{nullptr};
    std::atomic_bool _should_exit{false};
};

} // namespace dronecode_sdk

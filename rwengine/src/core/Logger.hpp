#ifndef _RWENGINE_LOGGER_HPP_
#define _RWENGINE_LOGGER_HPP_

#include <initializer_list>
#include <string>
#include <vector>

/**
 * Handles and stores messages from different components
 *
 * Dispatches received messages to logger outputs.
 */
class Logger {
public:
    enum MessageSeverity { Verbose, Info, Warning, Error };

    struct LogMessage {
        /// The component that produced the message
        std::string component;
        /// Severity of the message.
        MessageSeverity severity;
        /// Logged message
        std::string message;

        LogMessage(const std::string& cc, MessageSeverity ss,
                   const std::string& mm)
            : component(cc), severity(ss), message(mm) {
        }
    };

    /**
     * Interface for handling logged messages.
     *
     * The Logger class will not clean up allocated MessageReceivers.
     */
    struct MessageReceiver {
        virtual void messageReceived(const LogMessage&) = 0;
    };

    Logger(std::initializer_list<MessageReceiver*> initial = {})
        : receivers(initial) {
    }

    void addReceiver(MessageReceiver* out);
    void removeReceiver(MessageReceiver* out);

    void log(const std::string& component, Logger::MessageSeverity severity,
             const std::string& message);

    void verbose(const std::string& component, const std::string& message);
    void info(const std::string& component, const std::string& message);
    void warning(const std::string& component, const std::string& message);
    void error(const std::string& component, const std::string& message);

private:
    std::vector<MessageReceiver*> receivers;
};

class StdOutReceiver : public Logger::MessageReceiver {
    void messageReceived(const Logger::LogMessage&) override;
};

#endif

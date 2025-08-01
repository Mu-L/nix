#pragma once
///@file
#include "store-config-private.hh"
#if NIX_WITH_S3_SUPPORT

#  include "nix/util/ref.hh"

#  include <optional>
#  include <string>

namespace Aws {
namespace Client {
struct ClientConfiguration;
}
} // namespace Aws

namespace Aws {
namespace S3 {
class S3Client;
}
} // namespace Aws

namespace nix {

struct S3Helper
{
    ref<Aws::Client::ClientConfiguration> config;
    ref<Aws::S3::S3Client> client;

    S3Helper(
        const std::string & profile,
        const std::string & region,
        const std::string & scheme,
        const std::string & endpoint);

    ref<Aws::Client::ClientConfiguration>
    makeConfig(const std::string & region, const std::string & scheme, const std::string & endpoint);

    struct FileTransferResult
    {
        std::optional<std::string> data;
        unsigned int durationMs;
    };

    FileTransferResult getObject(const std::string & bucketName, const std::string & key);
};

} // namespace nix

#endif

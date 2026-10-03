#if !defined(RESIP_TLSCLIENTIDENTITY_HXX)
#define RESIP_TLSCLIENTIDENTITY_HXX

#include "rutil/Data.hxx"

namespace resip
{

struct TlsClientIdentity
{
   TlsClientIdentity() = default;

   TlsClientIdentity(const Data& certificateChainFilename,
                     const Data& privateKeyFilename,
                     const Data& privateKeyPassPhrase = Data::Empty)
      : certificateChainFilename(certificateChainFilename),
        privateKeyFilename(privateKeyFilename),
        privateKeyPassPhrase(privateKeyPassPhrase)
   {
   }

   bool empty() const noexcept
   {
      return certificateChainFilename.empty() && privateKeyFilename.empty();
   }

   bool complete() const noexcept
   {
      return !certificateChainFilename.empty() && !privateKeyFilename.empty();
   }

   Data connectionKey() const
   {
      if(empty())
      {
         return Data::Empty;
      }

      // The pass phrase is deliberately excluded from the connection key.
      return certificateChainFilename + Data("\n") + privateKeyFilename;
   }

   Data certificateChainFilename;
   Data privateKeyFilename;
   Data privateKeyPassPhrase;
};

}

#endif

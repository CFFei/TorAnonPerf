
#include "tokenbucket.h"
#include "ns3/log.h"

using namespace std;
namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("TokenBucket");

TokenBucket::TokenBucket ()
{
  NS_LOG_FUNCTION (this);
}

TokenBucket::TokenBucket (DataRate rate, DataRate burst, Time refilltime)
{
  NS_LOG_FUNCTION (this);
  m_rate = rate;
  m_burst = burst;
  m_refilltime = refilltime;
}

TokenBucket::~TokenBucket ()
{
  NS_LOG_FUNCTION (this);
  Simulator::Remove (m_refillevent);
}

void
TokenBucket::SetRefilledCallback (Callback<void,int64_t> cb)
{
  m_refilled = cb;
}

void
TokenBucket::StartBucket (Time offset)
{
  m_bucket = m_burst.GetBitRate () / 8;
  m_refillevent = Simulator::Schedule (offset,&TokenBucket::Refill, this);
}

uint32_t
TokenBucket::GetSize ()
{
  if (m_bucket <= 0)
    {
      return 0;
    }
  return m_bucket;
}

void
TokenBucket::Decrement (uint32_t n)
{
  m_bucket -= n;
}

void
TokenBucket::Refill ()
{
  int64_t prev_bucket = m_bucket;
  int64_t rate = m_rate.GetBitRate () / 8;
  int64_t burst = m_burst.GetBitRate () / 8;
  m_bucket += rate * m_refilltime.GetSeconds ();
  if (burst < m_bucket)
    {
      m_bucket = burst;
    }

  if (!m_refilled.IsNull ())
    {
      m_refilled (prev_bucket);
    }

  m_refillevent = Simulator::Schedule (m_refilltime,&TokenBucket::Refill, this);
}

} //namespace ns3
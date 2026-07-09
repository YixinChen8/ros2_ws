#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to more_interfaces__msg__AddressBook

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct AddressBook {

    // This member is not documented.
    #[allow(missing_docs)]
    pub first_name: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub last_name: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub phone_number: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub phone_type: u8,

}

impl AddressBook {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const PHONE_TYPE_HOME: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const PHONE_TYPE_WORK: u8 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const PHONE_TYPE_MOBILE: u8 = 2;

}


impl Default for AddressBook {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::AddressBook::default())
  }
}

impl rosidl_runtime_rs::Message for AddressBook {
  type RmwMsg = super::msg::rmw::AddressBook;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        first_name: msg.first_name.as_str().into(),
        last_name: msg.last_name.as_str().into(),
        phone_number: msg.phone_number.as_str().into(),
        phone_type: msg.phone_type,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        first_name: msg.first_name.as_str().into(),
        last_name: msg.last_name.as_str().into(),
        phone_number: msg.phone_number.as_str().into(),
      phone_type: msg.phone_type,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      first_name: msg.first_name.to_string(),
      last_name: msg.last_name.to_string(),
      phone_number: msg.phone_number.to_string(),
      phone_type: msg.phone_type,
    }
  }
}



const Promise = require('bluebird');
const mongoose = require('mongoose');
const httpStatus = require('http-status');
const APIError = require('../helpers/APIError');

/**
 * Company Schema
 */
const CompanySchema = new mongoose.Schema({
  name: {
    type: String,
    required: true
  },
  information: {
    type: String,
    required: true,
  },
  loc: {
    type: { type: String , default: "Point"},
    coordinates: [],
    required: false
  },
  category: {
    type: String,
    required: false
  }
});

/**
 * Add your
 * - pre-save hooks
 * - validations
 * - virtuals
 */

 /**
  * Index
  */
CompanySchema.index({"loc" : "2dsphere"});

/**
 * Methods
 */
CompanySchema.method({
});

/**
 * Statics
 */
CompanySchema.statics = {
  /**
   * Get user
   * @param {ObjectId} id - The objectId of user.
   * @returns {Promise<User, APIError>}
   */
  get(id) {
    return this.findById(id)
      .exec()
      .then((company) => {
        if (company) {
          return company;
        }
        const err = new APIError('No such user exists!', httpStatus.NOT_FOUND);
        return Promise.reject(err);
      });
  },

  /**
   * List users in descending order of 'createdAt' timestamp.
   * @param {number} skip - Number of users to be skipped.
   * @param {number} limit - Limit number of users to be returned.
   * @returns {Promise<User[]>}
   */
  list({ skip = 0, limit = 50 } = {}) {
    return this.find()
      .sort({ createdAt: -1 })
      .skip(+skip)
      .limit(+limit)
      .exec();
  }
};

/**
 * @typedef Company
 */
module.exports = mongoose.model('Company', CompanySchema);
